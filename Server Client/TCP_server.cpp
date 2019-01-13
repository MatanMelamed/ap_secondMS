#include "TCP_server.h"

server_side::TCP_client server_side::TCP_server::Accept() {
    sockaddr_in addr{};
    socklen_t len = sizeof(addr);
    std::cout << "TCP_server::Accept() waiting for client.\n";
    int client_sock_fd = ::accept(_sock.sock_fd, (sockaddr *) &addr,
                                  &len);
    std::cout << "TCP_server::Accept() got client: " << client_sock_fd << "\n";

    if (client_sock_fd < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            close();
            std::cout << "TCP_server::Accept() Timeout occured.\n";
            return TCP_client();
        } else {
            throw MyException(ERR_ACCEPT);
        }
    }

    TCP_socket client_sock(client_sock_fd);

    client_sock.settimeout(0);

    return client_sock;
}

void server_side::TCP_server::createSocket(int port) {
    sockaddr_in addr_in{};
    addr_in.sin_family = AF_INET;
    addr_in.sin_addr.s_addr = INADDR_ANY;
    addr_in.sin_port = htons(static_cast<uint16_t>(port));

    Guard(bind(_sock.sock_fd, (sockaddr *) &addr_in, sizeof(addr_in)),
          ERR_BIND);
}

void server_side::TCP_server::listen(int max_lis) {
    Guard(::listen(_sock.sock_fd, max_lis), ERR_LISTEN);
}


