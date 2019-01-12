#include "SearchableHeuristicMatrix.h"

double SearchableHeuristicMatrix::GetHeuristic(State<Cell> *state) {

    double result;
    auto it = heuristics.find(state->GetData());
    if (it != heuristics.end()) {
        result = (*it).second;
    } else {
        Cell cell = state->GetData();
        Cell end = _exitStateIndicator.GetData();
        result = sqrt((cell.row - end.row) *
                            (cell.row - end.row) +
                            (cell.column - end.column) *
                            (cell.column - end.column));
        heuristics[cell] = result;
    }

    return result;
}

std::vector<std::pair<double, State<Cell> *>>
SearchableHeuristicMatrix::GetReachableNHeuristic(State<Cell> *state) {

    std::vector<std::pair<double, State<Cell> *>> result;

    std::vector<State<Cell> *> neighbors = GetReachable(state);
    for (State<Cell> *neighbor : neighbors) {
        result.emplace_back(GetHeuristic(neighbor), neighbor);
    }

    return result;
}


