#ifndef AP_SECONDMS_CELL_H
#define AP_SECONDMS_CELL_H

#include <ostream>

struct Cell {
public:
    int row;
    int column;

    bool operator==(const Cell &c) const {
        return (this->row == c.row) && (this->column == c.column);
    }

    bool operator<(const Cell &c) const {
        return row < c.row && column < c.column;
    }

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell) {
        os << "row: " << cell.row << " column: " << cell.column;
        return os;
    }
};


#endif
