//
// Created by tomme on 12/01/2019.
//

#include "MatrixSolver.h"

MatrixSolver::MatrixSolver(Searcher<Cell> *searcher) {
    this->searcher = searcher;
}
string MatrixSolver:: solve(SearchableMatrix* problem) {
    std::vector<State<Cell> *> result = searcher->Search(problem);
    State<Cell> father = *result[result.size() - 2];
    State<Cell> current = *result[result.size() - 3];
    string moves = "";
    for (int i = result.size() - 3; i >= 0;) {
        if (father.GetData().row < current.GetData().row &&
                father.GetData().column == current.GetData().column){
            moves = moves + DOWN;
        }
        if (father.GetData().row > current.GetData().row &&
                father.GetData().column == current.GetData().column) {
            moves = moves + UP;
        }
        if (father.GetData().column < current.GetData().column &&
            father.GetData().row == current.GetData().row    ) {
            moves = moves + RIGHT;
        }
        if (father.GetData().column > current.GetData().column &&
                father.GetData().row == current.GetData().row  ) {
            moves = moves + LEFT;
        }
        moves = moves + ",";
        father = current;
        if (i > 0) {
            current = *result[--i];
        } else { break; }
    }
    moves = moves.substr(0, moves.length() - 1);
    for (int i = 0; i < result.size(); i++) {
        State<Cell> *state = result[i];
        delete (state);
    }
    return moves;
}
MatrixSolver::~MatrixSolver(){}
