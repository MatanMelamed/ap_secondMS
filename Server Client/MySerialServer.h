#ifndef AP_SECONDMS_MYSERIALSERVER_H
#define AP_SECONDMS_MYSERIALSERVER_H

#include <pthread.h>
#include "TCP_server.h"

class MySerialServer;

struct ThreadParams {
    MySerialServer *_server;
    server_side::ClientHandler *_clientHandler;
};

class MySerialServer : public server_side::TCP_server {

public:
    MySerialServer();

    static void *Start(void *args);

    void open(int port, server_side::ClientHandler *c) override;

    void close() override;

};

#endif
