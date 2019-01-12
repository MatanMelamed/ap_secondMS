#ifndef AP_SECONDMS_MYCLIENT_H
#define AP_SECONDMS_MYCLIENT_H

#include "ClientHandler.h"

class MyTestClientHandler : public server_side::ClientHandler {


public:

    void handleClient(int clientSock) override;

};


#endif
