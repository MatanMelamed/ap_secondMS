
#include <iostream>

#include "SearchableMatrix.h"
#include "BFS.h"
void f() {
    std::vector<int> v = {1, -1, 2,
                          1, -1, 2,
                          1, 1, 1};
    SearchableMatrix m = SearchableMatrix(3);
    m.SetData(v);
    Cell c{0, 0};
    m.SetInitalState(c);
    c.row = 2;
    c.column = 2;
    m.SetExitState(c);

    BFS<Cell> bfs;
    std::vector<State<Cell>*> r = bfs.Search(&m);
    std::cout <<"";

}


int main() {

    f();


    return 0;
}
