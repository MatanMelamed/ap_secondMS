#ifndef AP_SECONDMS_SEARCHABLEHEURISTICMATRIX_H
#define AP_SECONDMS_SEARCHABLEHEURISTICMATRIX_H

#include <math.h>
#include <unordered_map>
#include "SearchableMatrix.h"
#include "SearchableHeuristic.h"

class SearchableHeuristicMatrix : public SearchableHeuristic<Cell>,
                                  public SearchableMatrix {
    std::unordered_map<Cell, int> heuristics;


public:
    explicit SearchableHeuristicMatrix(int rows, int cols) :
            SearchableMatrix(rows, cols) {};

    std::vector<std::pair<int, State<Cell> *>>
    GetReachableNHeuristic(State<Cell> *state) override;

    int GetHeuristic(State<Cell> *state) override;
};

#endif