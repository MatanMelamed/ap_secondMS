#include <cstring>
#include "MySerialServer.h"

pthread_t MySerialServer::open(int port, server_side::ClientHandler *c) {
    createSocket(port);
    SetTimeout(DEF_TIMEOUT);
    auto *params = new ThreadParams();
    params->_server = this;
    params->_clientHandler = c;
    pthread_t trid;
    pthread_create(&trid, nullptr, MySerialServer::Start, params);
    return trid;
}

void *MySerialServer::Start(void *args) {
    auto *params = (ThreadParams *) args;

    params->_server->listen(SOMAXCONN);

    while (!params->_server->ShouldStop()) {
        server_side::TCP_client client = params->_server->Accept();
        params->_clientHandler->handleClient(client);
    }

    params->_server->CloseSock();

    return nullptr;
}

void MySerialServer::close() {
    _shouldStop = true;
}


