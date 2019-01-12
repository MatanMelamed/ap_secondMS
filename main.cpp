
#include <iostream>
#include "SearchableHeuristicMatrix.h"
#include "Astar.h"

void f() {
    std::vector<int> v = {1, -1, 2,
                          1, -1, 2,
                          1, 1, 1};
    SearchableHeuristicMatrix m = SearchableHeuristicMatrix(3, 3);
    m.SetData(v);
    Cell c{0, 0};
    m.SetInitialState(c);
    c.row = 2;
    c.column = 2;
    m.SetExitState(c);

    Astar<Cell> astar;
    std::vector<State<Cell> *> r = astar.Search(&m);
    std::cout << "";

}


int main() {

    f();


    return 0;
}
