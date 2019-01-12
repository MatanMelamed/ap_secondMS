#ifndef AP_SECONDMS_BASECLIENTHANDLER_H
#define AP_SECONDMS_BASECLIENTHANDLER_H

#include "ClientHandler.h"
#include "../A and B/Solver.h"
#include "../A and B/CacheManager.h"

class BaseClientHandler : public server_side::ClientHandler {

    CacheManager * manager;


public:
    void handleClient(int clientSock) override = 0;

};

#endif
