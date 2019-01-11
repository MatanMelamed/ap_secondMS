#ifndef AP_SECONDMS_STATE_H
#define AP_SECONDMS_STATE_H

#include <iostream>

template<class T> // must have operator == !!!
class State {
    T _uniqueData;
    double _cost;
    State<T> *_cameFrom;

public:
    explicit State(T state,
                   double cost = 0,
                   State<T> *cameFrom = nullptr) : _uniqueData(state),
                                                   _cost(cost),
                                                   _cameFrom(cameFrom) {}

    bool operator==(const State<T> &right) const {
        return this->_uniqueData == right._uniqueData;
    }

    bool operator<(const State<T> &right) const {
        return this->_cost < right._cost;
    }

    double GetCost() const {
        return _cost;
    }

    void SetCost(double cost) {
        this->_cost = cost;
    }

    void SetData(T data) {
        this->_uniqueData = data;
    }

    T GetData() const {
        return _uniqueData;
    }

    State<T> *GetCameFrom() const {
        return _cameFrom;
    }

    void SetCameFrom(State<T> *_cameFrom) {
        State::_cameFrom = _cameFrom;
    }

    friend std::ostream &operator<<(std::ostream &os, const State &state) {
        os << "_uniqueData: " << state._uniqueData << " _cost: " << state._cost;
        return os;
    }

};

namespace std {
    template<class T>
    struct hash<State<T>> {
        size_t operator()(const State<T> &state) const {
            return hash<T>()(state.GetData());
        }
    };
}

#endif
