#include "Server Client/MySerialServer.h"
#include "Server Client/MyTestClientHandler.h"
#include "Solver And Cacher/MatrixSolver.h"
#include "Solver And Cacher/FileCacheManager.h"
#include "Algorithms/Astar.h"


void f() {

    MySerialServer server;

    auto *astar = new Astar<Cell>();
    auto *solver = new MatrixSolver(astar);
    auto *manager = new FileCacheManager();
    auto *handler = new MyTestClientHandler(solver, manager);

    pthread_t trid = server.open(5405, handler);

    pthread_join(trid, nullptr);

}

int main() {

    f();
    return 0;
}

