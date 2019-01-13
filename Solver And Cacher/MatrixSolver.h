#ifndef AP_SECONDMS_MATRIXSOLVER_H
#define AP_SECONDMS_MATRIXSOLVER_H

#include "Solver.h"
#include "../Algorithms/SearchableMatrix.h"
#include "../Algorithms/Searcher.h"
#include "../Algorithms/State.h"
#include "../Algorithms/Cell.h"
#include <vector>
#include "../Algorithms/BFS.h"
#include "../Algorithms/SearchableHeuristic.h"
#define UP "Up"
#define DOWN "Down"
#define RIGHT "Right"
#define LEFT "Left"
class MatrixSolver: public Solver<SearchableMatrix*,string> {
private:
    Searcher<Cell>* searcher;
public:
    MatrixSolver(Searcher<Cell>* searcher);
    string solve(SearchableMatrix* problem) override;
    ~MatrixSolver();
};


#endif //AP_SECONDMS_MATRIXSOLVER_H
