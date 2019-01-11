
#include <iostream>

#include "SearchableMatrix.h"
#include "BFS.h"
#include "PStateUnorderedSet.h"
#include "PStatePriQue.h"

void f() {
    std::vector<int> v = {1, -1, 2,
                          1, 2, 2,
                          1, 1, 1};
    SearchableMatrix m = SearchableMatrix(3);
    m.SetData(v);
    Cell c{0, 0};
    m.SetInitalState(c);
    c.row = 2;
    c.column = 2;
    m.SetExitState(c);

    BFS<Cell> bfs;
    bfs.Search(&m);
}


int main() {

    f();


    return 0;
}
