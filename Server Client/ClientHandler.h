#ifndef AP_SECONDMS_CLIENTHANDLER_H
#define AP_SECONDMS_CLIENTHANDLER_H

#include <string>

namespace server_side {
    class ClientHandler {

    public:
        virtual void handleClient(int clientSock) = 0;
    };
}

#endif
