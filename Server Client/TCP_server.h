#ifndef AP_SECONDMS_TCP_SERVER_H
#define AP_SECONDMS_TCP_SERVER_H

#include <arpa/inet.h>

#include "TCP_socket.h"
#include "../MyException.h"

#define ERR_BIND "failure on bind"
#define ERR_LISTEN "failure on listen"

namespace server_side {

    class TCP_server {

    protected:
        TCP_socket sock;

    public:
        TCP_server(int port) {
            sockaddr_in addr_in{};
            addr_in.sin_family = AF_INET;
            addr_in.sin_addr.s_addr = INADDR_ANY;
            addr_in.sin_port = htons(static_cast<uint16_t>(port));

            Guard(bind(sock.sock_fd, (sockaddr *) &addr_in, sizeof(addr_in)),
                  ERR_BIND);
        }

        void listen(int max_lis) {
            Guard(::listen(sock.sock_fd, max_lis), ERR_LISTEN);
        }

        void settimeout(int sec, int usec = 0) {
            sock.settimeout(sec, usec);
        }

        void close() {
            sock.close();
        }

    };
}

#endif
