#include "Boot.h"


int server_side::boot::Main::main(int argc, char **argv) {

    MySerialServer server;

    auto *solver = new StringReverser();
    auto *manager = new FileCacheManager();
    auto *handler = new MyTestClientHandler(solver, manager);

    pthread_t trid = server.open(5405, handler);

    pthread_join(trid, nullptr);


    return 0;
}
