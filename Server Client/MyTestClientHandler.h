#ifndef AP_SECONDMS_MYCLIENT_H
#define AP_SECONDMS_MYCLIENT_H

#include "ClientHandler.h"
#include "../Solver And Cacher/Solver.h"
#include "../Solver And Cacher/CacheManager.h"

class MyTestClientHandler : public server_side::ClientHandler {

    Solver<std::string, std::string> *solver;
    CacheManager<std::string, std::string> *manager;

public:
    MyTestClientHandler();

    void handleClient(server_side::TCP_client clientSock) override;

};


#endif
