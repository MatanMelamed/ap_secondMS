#ifndef AP_SECONDMS_TCP_SOCKET_H
#define AP_SECONDMS_TCP_SOCKET_H

#include <sys/socket.h>
#include <unistd.h>
#include "../Etc/MyException.h"

#define ERR_OPEN "failure on opening socket"
#define ERR_CLOSE "failure on closing socket"
#define ERR_OPT "failure on setsockopt"
namespace server_side {

    struct TCP_socket {
        int sock_fd;

        TCP_socket() {
            sock_fd = Guard(socket(AF_INET, SOCK_STREAM, 0), ERR_OPEN);
        }

        TCP_socket(int open_sock_fd) {
            this->sock_fd = open_sock_fd;
        }

        void close() {
            Guard(::close(sock_fd), ERR_CLOSE);
        }

        void settimeout(int sec, int usec = 0) {
            timeval timeout{};
            timeout.tv_sec = sec;
            timeout.tv_usec = usec;

            // setting socket option for recieve timeout
            Guard(setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO,
                             (char *) &timeout, sizeof(timeout)), ERR_OPT);
        }
    };
}
#endif
