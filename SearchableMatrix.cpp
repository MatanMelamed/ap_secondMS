
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
    LoadValidMovements();
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
    this->_validMovements = other._validMovements;
    return *this;
}

SearchableMatrix &SearchableMatrix::operator=(const SearchableMatrix &other) {
    this->_entrance = other._entrance;
    this->_exitStateIndicator = other._exitStateIndicator;
    this->_validMovements = other._validMovements;
    for (int i = 0; i < _rowLength; ++i) {
        for (int j = 0; j < _rowLength; ++j) {
            this->_matrix[i][j] = other._matrix[i][j];
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
    if (_validMovements.empty()) {
        _validMovements.push_back({1,0});
        _validMovements.push_back({-1,0});
        _validMovements.push_back({0, -1});
        _validMovements.push_back({0, 1});
    }
}

void SearchableMatrix::SetData(std::vector<int> &data) {

    for (int i = 0; i < _rowLength; i++) {
        for (int j = 0; j < _rowLength; j++) {
            try {
                _matrix[i][j] = data[i + j];
            } catch (const std::out_of_range &exp) {
                throw MyException(INVAL_INFO);
            }
        }
    }
}

void SearchableMatrix::SetInitalState(Cell start) {
    if (IsInMatrix(start.row, start.column)) {
        throw MyException(OUT_OF_BOUNDRY);
    }
    this->_entrance = start;
}

void SearchableMatrix::SetExitState(Cell end) {
    if (IsInMatrix(end.row, end.column)) {
        throw MyException(OUT_OF_BOUNDRY);
    }
    this->_exitStateIndicator.SetState(end);
}


// Searchable Override Functions
State<Cell> SearchableMatrix::GetInitialState() {
    return {_entrance};
}

bool SearchableMatrix::isGoal(State<Cell> &state) {
    return state == _exitStateIndicator;
}

bool SearchableMatrix::IsInMatrix(int x, int y) const {
    return (0 <= x && x <= _rowLength) &&
           (0 <= y && y <= _rowLength);
}

std::vector<State<Cell> > SearchableMatrix::GetReachable(State<Cell>
                                                         &state) {
    std::vector<State<Cell> > result;
    for (Cell movement : _validMovements) {
        int newX = state.GetState().row + movement.row;
        int newY = state.GetState().column + movement.column;
        if (IsInMatrix(newX, newY)) {
            if (_matrix[newX][newY] != WALL_VAL) {
                result.push_back(State<Cell>({newX, newY}, _matrix[newX][newY],
                                             &state));
            }
        }
    }

    return result;
}
