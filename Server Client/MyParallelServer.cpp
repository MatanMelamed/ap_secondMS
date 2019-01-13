#include "MyParallelServer.h"
#include <pthread.h>

pthread_t MyParallelServer::open(int port, server_side::ClientHandler *c) {
    createSocket(port);
    SetTimeout(DEF_TIMEOUT);

    auto *params = new ThreadParams();
    params->_server = this;
    params->_clientHandler = c;
    pthread_t trid;
    pthread_create(&trid, nullptr, MyParallelServer::Start, params);
    return trid;
}

void *MyParallelServer::Start(void *args) {
    auto *params = (ThreadParams *) args;

    params->_server->listen(SOMAXCONN);

    while (!params->_server->ShouldStop()) {
        server_side::TCP_client client = params->_server->Accept();

        auto *cliParams = new CliThreadParams();
        cliParams->clientSock = client;
        cliParams->handler = params->_clientHandler->Clone();
        cliParams->server = params->_server;

        params->_server->AddClient(cliParams);
    }

    params->_server->CloseAll();
    delete params->_clientHandler;
    delete params;

    return nullptr;
}

void *MyParallelServer::DoClient(void *args) {
    auto *cliParams = (CliThreadParams *) args;
    cliParams->handler->handleClient(cliParams->clientSock);
    cliParams->server->UpdateThreadVector(pthread_self(), DELETE);
    delete cliParams->handler;
    delete cliParams;
    return nullptr;
}

MyParallelServer::MyParallelServer() {}

void MyParallelServer::close() {
    _shouldStop = true;
}

void MyParallelServer::AddClient(CliThreadParams *cliParams) {
    pthread_t newClient;
    pthread_create(&newClient, nullptr, MyParallelServer::DoClient, cliParams);
    UpdateThreadVector(newClient);
    std::cout << "MyParallelServer::AddClient() new cli added\n";
    std::cout << "MyParallelServer::AddClient() vec size: "
              << to_string(_clientThreads.size()) << "\n";
}

void MyParallelServer::CloseAll() {
    for (pthread_t thread : _clientThreads) {
        pthread_join(thread, nullptr);
    }
}

void MyParallelServer::UpdateThreadVector(pthread_t pthread, int operation) {
    lock.lock();
    if (operation == ADD) {
        _clientThreads.push_back(pthread);
    } else if (operation == DELETE) {
        std::vector<pthread_t>::iterator it;
        for (it = _clientThreads.begin(); it != _clientThreads.end(); ++it) {
            if (*it == pthread) {
                _clientThreads.erase(it);
                break;
            }
        }
    }
    lock.unlock();
}


