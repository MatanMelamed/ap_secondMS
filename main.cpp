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


void g() {

    SearchableMatrix m(3, 5);
    std::vector<int> data = {1, -1, 1, 1, 1,
                             1, -1, 1, -1, 1,
                             1, 1, 1, -1, 1};
    m.SetData(data);
    m.SetInitialState({0, 0});
    m.SetExitState({2, 4});

    auto *astar = new Astar<Cell>();
    auto *solver = new MatrixSolver(astar);
    std::string results = solver->solve(&m);
    std::cout << results;


}

int main() {

    g();
    return 0;
}

