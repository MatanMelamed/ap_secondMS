
#include "SearchableMatrix.h"

// Constructors and Destructor
void SearchableMatrix::AllocateMatrix() {

    _matrix = new int *[_rowLength];

    for (int i = 0; i < _rowLength; i++) {
        _matrix[i] = new int[_rowLength];
    }
}

SearchableMatrix::SearchableMatrix(int _rowLength) : _rowLength(_rowLength),
                                                     _matrix(nullptr),
                                                     _exitStateIndicator({}) {
    LoadValidMovements();
    if (_rowLength < MINIMUM_SIZE) { throw MyException(SIZE_ERR); }
    AllocateMatrix();
}

SearchableMatrix::SearchableMatrix(SearchableMatrix &&other) noexcept
        : _exitStateIndicator({}) {
    this->_rowLength = other._rowLength;
    this->_matrix = other._matrix;
    other._matrix = nullptr;
    this->_entrance = other._entrance;
    this->_exitStateIndicator = other._exitStateIndicator;
}

SearchableMatrix::SearchableMatrix(const SearchableMatrix &other)
        : SearchableMatrix(other._rowLength) {
    (*this) = other; // copy assignment
}

SearchableMatrix::~SearchableMatrix() {
    if (_matrix != nullptr) {
        for (int i = 0; i < _rowLength; ++i) {
            if (_matrix[i] != nullptr) {
                delete _matrix[i];
            }
        }
    }
}

SearchableMatrix &SearchableMatrix::operator=(SearchableMatrix &&other)
noexcept {
    this->_rowLength = other._rowLength;
    this->_matrix = other._matrix;
    other._matrix = nullptr;
    this->_entrance = other._entrance;
    this->_exitStateIndicator = other._exitStateIndicator;
    return *this;
}

SearchableMatrix &SearchableMatrix::operator=(const SearchableMatrix &other) {
    this->_entrance = other._entrance;
    this->_exitStateIndicator = other._exitStateIndicator;
    for (int i = 0; i < _rowLength; ++i) {
        for (int j = 0; j < _rowLength; ++j) {
            other._matrix[i][j] = this->_matrix[i][j];
        }
    }
    return *this;
}


// Class Specific Functions
State<Cell> *SearchableMatrix::GetStateInOffSetOf(State<Cell> *base,
                                                  int xDir,
                                                  int yDir) {
    State<Cell> *result = nullptr;
    if (xDir < _rowLength && yDir < _rowLength) {
        if (_matrix[xDir][yDir] != WALL_VAL) {
            result = new State<Cell>({xDir, yDir}, _matrix[xDir][yDir], base);
        }
    }
    return result;
}

void SearchableMatrix::LoadValidMovements() {
    if (SearchableMatrix::ValidMovements.empty()) {
        ValidMovements.push_back({1, 1});
        ValidMovements.push_back({-1, -1});
        ValidMovements.push_back({1, -1});
        ValidMovements.push_back({-1, 1});
    }
}

void SearchableMatrix::SetData(std::vector<int> &data) {

    for (int i = 0; i < _rowLength; i++) {
        for (int j = 0; j < _rowLength; j++) {
            _matrix[i][j] = data[i + j];
        }
    }
}

void SearchableMatrix::SetInitalState(Cell start) {
    if (start.column > _rowLength || start.row > _rowLength) {
        throw MyException(OUT_OF_BOUNDRY);
    }
    this->_entrance = start;
}

void SearchableMatrix::SetExitState(Cell end) {
    if (end.column > _rowLength || end.row > _rowLength) {
        throw MyException(OUT_OF_BOUNDRY);
    }
    this->_exitStateIndicator.SetState(end);
}


// Searchable Override Functions
State<Cell> *SearchableMatrix::GetInitialState() {
    return new State<Cell>({_entrance});
}

bool SearchableMatrix::isGoal(State<Cell> &state) {
    return state == _exitStateIndicator;
}

std::vector<State<Cell> *> SearchableMatrix::GetReachable(State<Cell>
                                                          &state) {
    std::vector<State<Cell> *> result;
    State<Cell> *tmp;

    for (Cell movement : SearchableMatrix::ValidMovements) {
        tmp = GetStateInOffSetOf(&state, movement.row, movement.column);
        if (tmp != nullptr) {
            result.push_back(tmp);
        }
    }

    return result;
}
