#ifndef AP_SECONDMS_SEARCHABLEHEURISTICMATRIX_H
#define AP_SECONDMS_SEARCHABLEHEURISTICMATRIX_H

#include <math.h>
#include <unordered_map>
#include "SearchableMatrix.h"
#include "SearchableHeuristic.h"

class SearchableHeuristicMatrix : public SearchableMatrix,
                                  public SearchableHeuristic<Cell> {
    std::unordered_map<Cell, double> heuristics;

public:
    explicit SearchableHeuristicMatrix(int rows, int cols) :
            SearchableMatrix(rows, cols) {};

    std::vector<std::pair<double, State<Cell> *>>
    GetReachableNHeuristic(State<Cell> *state) override;

    double GetHeuristic(State<Cell> *state) override;
};

#endif