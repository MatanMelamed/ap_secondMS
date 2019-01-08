#ifndef AP_SECONDMS_STATE_H
#define AP_SECONDMS_STATE_H

template<class T> // must have operator == !!!
class State {
    T _state;
    double _cost;
    State<T> *_cameFrom;

public:
    State(T state,
          double cost = 0,
          State<T> *cameFrom = nullptr) : _state(state),
                                          _cost(cost),
                                          _cameFrom(cameFrom) {}

    bool operator==(const State<T> &right) {
        return (*this)._state == right._state;
    }

    double getCost() const {
        return _cost;
    }

    void setCost(double cost) {
        this->_cost = cost;
    }

    void SetState(T state){
        this->_state = _state;
    }

    T get_state() const {
        return _state;
    }

};

#endif
