#ifndef AP_SECONDMS_SEARCHERHEURISTIC_H
#define AP_SECONDMS_SEARCHERHEURISTIC_H

#include "SearchableHeuristic.h"

template<typename T>
class SearcherHeuristic {

public:
    virtual std::vector<State<T> *> Search(SearchableHeuristic<T> *s) = 0;
};

#endif
