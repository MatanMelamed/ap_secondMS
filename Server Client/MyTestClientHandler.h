#ifndef AP_SECONDMS_MYCLIENT_H
#define AP_SECONDMS_MYCLIENT_H

#include "ClientHandler.h"
#include "../A and B/Solver.h"
#include "../A and B/CacheManager.h"

class MyTestClientHandler : public server_side::ClientHandler {


public:

    void handleClient(int clientSock) override;

};


#endif
