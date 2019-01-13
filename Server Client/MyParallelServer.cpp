#include "MyParallelServer.h"
#include <pthread.h>

void MyParallelServer::open(int port, server_side::ClientHandler *c) {
    createSocket(port);
    auto *params = new ThreadParams();
    params->_server = this;
    params->_clientHandler = c;
    pthread_t trid;
    pthread_create(&trid, nullptr, MyParallelServer::Start, params);
}

void *MyParallelServer::Start(void *args) {
    auto *params = (ThreadParams *) args;

    params->_server->listen(SOMAXCONN);

    while (!params->_server->ShouldStop()) {
        server_side::TCP_client client = params->_server->Accept();

        auto *cliParams = new CliThreadParams();
        cliParams->clientSock = client;
        cliParams->handler = params->_clientHandler;

        params->_server->AddClient(cliParams);
    }

    params->_server->CloseAll();
    delete params;

    return nullptr;
}

void *MyParallelServer::DoClient(void *args) {
    auto *cliParams = (CliThreadParams *) args;
    cliParams->handler->handleClient(cliParams->clientSock);
    delete cliParams;
    return nullptr;
}

MyParallelServer::MyParallelServer() {
    SetTimeout(DEF_TIMEOUT);
}

void MyParallelServer::close() {
    _shouldStop = true;
}

void MyParallelServer::AddClient(CliThreadParams *cliParams) {
    pthread_t newClient;
    pthread_create(&newClient, nullptr, MyParallelServer::DoClient, cliParams);
    _clientThreads.push_back(newClient);
}

void MyParallelServer::CloseAll() {
    for (pthread_t thread : _clientThreads) {
        pthread_join(thread, nullptr);
    }
}


