#include "Server Client/MySerialServer.h"
#include "Server Client/MyTestClientHandler.h"
#include "Solver And Cacher/MatrixSolver.h"
#include "Solver And Cacher/FileCacheManager.h"
#include "Algorithms/Astar.h"
#include "Algorithms/DFS.h"

#define ERR_NO_PORT "Program must receive port number"

int main(int argc, char **argv) {

    if (argc == 1) { throw MyException(ERR_NO_PORT); }


    MySerialServer server;

    auto *astar = new Astar<Cell>();
    auto *solver = new MatrixSolver(astar);
    auto *manager = new FileCacheManager();
    auto *handler = new MyTestClientHandler(solver, manager);

    pthread_t trid = server.open(5405, handler);

    pthread_join(trid, nullptr);

    return 0;
}

