#ifndef AP_SECONDMS_SEARCHABLEHEURISTIC_H
#define AP_SECONDMS_SEARCHABLEHEURISTIC_H

#include "Searchable.h"

template<typename T>
class SearchableHeuristic : virtual public Searchable<T> {
public:
    virtual std::vector<std::pair<int, State<T> *>>
    GetReachableNHeuristic(State<T> *state) = 0;

    virtual int GetHeuristic(State<T> *state) = 0;

};

#endif
