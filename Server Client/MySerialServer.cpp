#include <cstring>
#include "MySerialServer.h"

void MySerialServer::open(int port, server_side::ClientHandler *c) {
    createSocket(port);
    auto *params = new ThreadParams();
    params->_server = this;
    params->_clientHandler = c;
    pthread_t trid;
    pthread_create(&trid, nullptr, MySerialServer::Start, params);
    _servThrd = trid;
}

void MySerialServer::createSocket(int port) {

    _serverSocket = Guard(socket(AF_INET, SOCK_STREAM, 0), ERR_SCK_OPN);
    int flags = Guard(fcntl(_serverSocket, F_GETFL), ERR_SCK_FLG_GET);
    Guard(fcntl(_serverSocket, F_SETFL, flags | O_NONBLOCK), ERR_SCK_FLG_SET);

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(static_cast<uint16_t>(port));

    /* Now bind the host address using bind() call.*/
    Guard(bind(_serverSocket, (struct sockaddr *) &serv_addr,
               sizeof(serv_addr)), ERR_SCK_BND);
}

void *MySerialServer::Start(void *args) {
    auto *params = (ThreadParams *) args;

    while (!params->_server->ShouldStop()) {
        params->_server->waitForClient();

        if (params->_server->IsConnectedToClient()) {
            params->_server->CommunicateWithClient(params->_clientHandler);
        }
    }

    return nullptr;
}

void MySerialServer::waitForClient() {

    listen(_serverSocket, MAX_CNT);

    while (!ShouldStop()) {
        // check once, if no requests but without error, then sleep, else error.
        _clientSocket = accept(_serverSocket, nullptr, nullptr);
        if (_clientSocket == ERROR_NO) {
            if (errno == EWOULDBLOCK) {
                sleep(WAIT_INTERVAL);
            } else {
                throw MyException(ERR_SCK_ACPT);
            }
        } else {
            break;
        }
    }
}


void MySerialServer::CommunicateWithClient(server_side::ClientHandler *c) {
    c->handleClient(_clientSocket);
    _clientSocket = ERROR_NO;
}


