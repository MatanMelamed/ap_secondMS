#ifndef AP_SECONDMS_ALGORITHM_H
#define AP_SECONDMS_ALGORITHM_H

#include <vector>
#include "State.h"

template<class T>
class Searchable {

public:
    virtual State<T> *GetInitialState() = 0;

    virtual bool isGoal(State<T> *state) = 0;

    virtual std::vector<State<T> *> GetReachable(State<T> *state) = 0;

    virtual State<T> *GetDummy() = 0;
};

#endif