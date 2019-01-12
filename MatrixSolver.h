#ifndef AP_SECONDMS_MATRIXSOLVER_H
#define AP_SECONDMS_MATRIXSOLVER_H

#include <iostream>
#include "Solver.h"
#include "Searcher.h"
#include "BFS.h"
#include "SearchableMatrix.h"

class MatrixSolver : public Solver<SearchableMatrix, std::string> {
    Searcher<Cell> *algo;

public:

    std::string Solve(SearchableMatrix *problem) override {

        algo->Search(problem);

        return Solver::Solve(problem);
    }
};

#endif
