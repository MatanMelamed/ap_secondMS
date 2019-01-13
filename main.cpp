#include "Server Client/MySerialServer.h"
#include "Server Client/MyTestClientHandler.h"
#include "Solver And Cacher/StringReverser.h"
#include "Solver And Cacher/FileCacheManager.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <iostream>

using namespace std;

void g(){
    MySerialServer s;

    MyTestClientHandler c = MyTestClientHandler(new StringReverser(),
                                                new FileCacheManager());
    pthread_t thread = s.open(5404, &c);

    pthread_join(thread, nullptr);
}


void f() {



    int port = 5404;
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(port);
    serv.sin_family = AF_INET;
    if (bind(s, (sockaddr *) &serv, sizeof(serv)) < 0) {
        cerr << "Bad!" << endl;
    }

    int new_sock;
    listen(s, 5);
    struct sockaddr_in client;
    socklen_t clilen = sizeof(client);

    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    new_sock = accept(s, (struct sockaddr *) &client, &clilen);
    if (new_sock < 0) {
        if (errno == EWOULDBLOCK) {
            cout << "timeout!" << endl;
            exit(2);
        } else {
            perror("other error");
            exit(3);
        }
    }
    cout << new_sock << endl;
    cout << s << endl;
    close(new_sock);
    close(s);
}
int main() {

    f();


    return 0;
}
