
#include <iostream>
#include "Algorithms/SearchableHeuristicMatrix.h"
#include "Algorithms/Astar.h"
#include "Algorithms/DFS.h"

void f() {
    std::vector<int> v = {1, -1, 2, 2,
                          1, 2, 1, 1,
                          1, 1, 1, 3,
                          3, 2, 1, 1};
    SearchableHeuristicMatrix m = SearchableHeuristicMatrix(4, 4);
    m.SetData(v);
    Cell c{0, 0};
    m.SetInitialState(c);
    c.row = 3;
    c.column = 3;
    m.SetExitState(c);

    Astar<Cell> astar;
    std::vector<State<Cell> *> r = astar.Search(&m);
    std::cout << "";

}


int main() {

    f();


    return 0;
}
