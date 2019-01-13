#include "Solver And Cacher/MatrixSolver.h"
#include "Solver And Cacher/FileCacheManager.h"
#include "Server Client/MyTestClientHandler.h"
#include "Algorithms/BFS.h"
#include "Algorithms/DFS.h"


int main() {

    SearchableMatrix m(5, 5);
    std::vector<int> data = {1, 8, 1, 1, 1,
                             1, 8, 1, 8, 1,
                             1, 8, 1, 8, 1,
                             1, 8, 1, 8, 1,
                             1, 1, 1, 8, 1,};
    m.SetData(data);
    m.SetInitialState({0, 0});
    m.SetInitialState({4, 4});

    BFS<Cell> bfs;
    DFS<Cell> dfs;
    MatrixSolver _solver(&bfs);
    FileCacheManager _manager = FileCacheManager();

    string problem = m.toString();
    string solution;

    if (_manager.IsSolutionExists(problem)) {
        solution = _manager.GetSolution(problem);
    } else {
        solution = _solver.solve(&m);
        _manager.SaveSolution(problem, solution);
    }

    std::cout << solution;
    return 0;
}

void fd(std::vector<State<Cell> *> &ve) {
    for (State<Cell> *cell : ve) {
        std::cout << *cell << std::endl;
    }
}

void f() {
    BFS<Cell> bfs;

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
    fd(r);
    std::cin.get();
    std::cout << "";
}
