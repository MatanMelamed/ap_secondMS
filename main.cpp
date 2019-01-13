#include "Server Client/MyTestClientHandler.h"
#include "Solver And Cacher/StringReverser.h"
#include "Solver And Cacher/FileCacheManager.h"
#include "Server Client/MyParallelServer.h"
#include "Algorithms/BestFS.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <pthread.h>
#include <iostream>

#include "Etc/client.h"

using namespace std;


void g() {
    MyParallelServer s;
    MyTestClientHandler c = MyTestClientHandler(new StringReverser(),
                                                new FileCacheManager());

    try {
        pthread_t thread = s.open(5404, &c);

        cin.get();
        s.close();
        pthread_join(thread, nullptr);
    } catch (MyException &ex) {
        std::cout << ex.GetMessage() << "\n";
        std::cout << ex.GetError().what();
    }
}

void f();

int main() {

    f();

    return 0;
}

void f() {
    BestFS<Cell> bfs;

    SearchableMatrix m(5, 5);

    std::vector<int> data = {1, 8, 1, 1, 1,
                             1, 8, 1, 8, 1,
                             1, 8, 1, 8, 1,
                             1, 8, 1, 8, 1,
                             1, 1, 1, 8, 1,};
    m.SetData(data);
    m.SetInitialState({0, 0});
    m.SetInitialState({4, 4});

    std::vector<State<Cell> *> r = bfs.Search(&m);

    std::cin.get();
    std::cout << "";


}
