#ifndef AP_SECONDMS_TCP_CLIENT_H
#define AP_SECONDMS_TCP_CLIENT_H

#include "TCP_client.h"
#include "../Utils.h"
#include "TCP_socket.h"

#define DEF_SIZE 256

#define ERR_READ "failure on reading from socket"

namespace server_side {

    class TCP_client {

    protected:
        char buffer[DEF_SIZE];
        string current_string;
        string leftovers;

        TCP_socket sock;

    public:

        TCP_client(TCP_socket sock) : sock(sock) {}

        std::string GetLine() {
            int numOfReceivedBytes;
            int bufferLen = (int) sizeof(buffer);
            for (;;) {
                bzero(buffer, bufferLen);
                numOfReceivedBytes = (int) read(sock.sock_fd, buffer,
                                                bufferLen - 1);
                if(errno == EAGAIN || errno = EWOULDBLOCK){
                    throw
                }
                if (ManageStrings(buffer, current_string, leftovers)) {
                    std::string line = current_string;
                    current_string.clear();
                    return line;
                    break;
                }
            }
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