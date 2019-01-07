#ifndef AP_SECONDMS_MYSERIALSERVER_H
#define AP_SECONDMS_MYSERIALSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <iostream>

#include "Server.h"
#include "MyException.h"

#define ERROR_NO -1
#define ERR_SCK_OPN "ERROR opening socket"
#define ERR_SCK_BND "ERROR on binding"
#define ERR_SCK_ACPT "ERROR on accept"
#define ERR_SCK_FLG_GET "could not get flags on TCP listening socket"
#define ERR_SCK_FLG_SET "could not set TCP listening socket to be non-blocking"
#define MAX_CNT 5
#define WAIT_INTERVAL 1 // sec to wait between tries

class MySerialServer;

struct ThreadParams {
    MySerialServer *_server;
    server_side::ClientHandler *_clientHandler;
};

class MySerialServer : public server_side::Server {

protected:
    bool _shouldStop;
    int _serverSocket;
    int _clientSocket;
    struct sockaddr_in serv_addr; // needed for each client accept
    pthread_t _servThrd;

    static void *Start(void *args);

    static int Guard(int resultNo, const std::string &message);

    bool IsConnectedToClient() const {
        return _clientSocket != -1;
    }

    bool ShouldStop() const { return _shouldStop; }

    void createSocket(int port);

    void waitForClient();

    void CommunicateWithClient(server_side::ClientHandler *c);


public:
    MySerialServer() : _serverSocket(-1),
                       _clientSocket(-1),
                       serv_addr(),
                       _shouldStop(false),
                       _servThrd() {}

    void open(int port, server_side::ClientHandler *c) override;

    void close() override {
        _shouldStop = true;
        pthread_join(_servThrd, nullptr);// wait until server thread is stopped.
    }
};

#endif
