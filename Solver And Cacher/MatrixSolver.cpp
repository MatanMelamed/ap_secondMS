#include "MatrixSolver.h"

MatrixSolver::MatrixSolver(Searcher<Cell> *searcher) {
    this->searcher = searcher;
}

string MatrixSolver::solve(SearchableMatrix *problem) {
    std::vector<State<Cell> *> result = searcher->Search(problem);
    State<Cell> father = *result[result.size() - 3];
    State<Cell> current = *result[result.size() - 2];
    string moves;
    for (int i = (int) (result.size() - 3); i >= 0;) {
        if (father.GetData().row < current.GetData().row &&
            father.GetData().column == current.GetData().column) {
            moves += DOWN;
        } else if (father.GetData().row > current.GetData().row &&
                   father.GetData().column == current.GetData().column) {
            moves += UP;
        } else if (father.GetData().column < current.GetData().column &&
                   father.GetData().row == current.GetData().row) {
            moves += RIGHT;
        } else if (father.GetData().column > current.GetData().column &&
                   father.GetData().row == current.GetData().row) {
            moves += LEFT;
        }
        moves += ",";
        current = father;
        if (i > 0) {
            father = *result[--i];
        } else { break; }
    }
    moves = moves.substr(0, moves.length() - 1);
    for (int i = 0; i < result.size(); i++) {
        State<Cell> *state = result[i];
        delete (state);
    }
    return moves;
}

MatrixSolver::~MatrixSolver() {
    delete searcher;
}

Solver<SearchableMatrix *, string> *MatrixSolver::Clone() {
    return new MatrixSolver(searcher->Clone());
}

