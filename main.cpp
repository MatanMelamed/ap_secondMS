#include "Server Client/MySerialServer.h"
#include "Server Client/MyTestClientHandler.h"
#include "Solver And Cacher/MatrixSolver.h"
#include "Solver And Cacher/FileCacheManager.h"
#include "Algorithms/Astar.h"


void f() {

    MySerialServer server;
    Astar<Cell> astar;
    MatrixSolver solver(&astar);
    FileCacheManager manager;

    MyTestClientHandler handler(&solver, &manager);

    pthread_t trid = server.open(5404, &handler);

    std::cin.get();
    std::cout << "force closing\n";
    server.close();

    pthread_join(trid, nullptr);

}

int main() {

    f();
    return 0;
}

