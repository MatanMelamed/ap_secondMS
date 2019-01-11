#ifndef AP_SECONDMS_CUSTOMQUEUE_H
#define AP_SECONDMS_CUSTOMQUEUE_H

#include <iostream>
#include <set>
#include <map>

#include "State.h"

template<class T>
struct StateCompare {
    bool operator()(const State<T> *l, const State<T> *r) const {
        return l->GetCost() < r->GetCost();
    }
};

template<class T>
class StatePriQue {
    std::map<T, typename std::multiset<State<T> *>::iterator> _elements;
    std::multiset<State<T> *, StateCompare<T>> _sorted_elements;
public:
    StatePriQue() = default;

    void Push(State<T> *state);

    void Remove(State<T> *state);

    void Update(State<T> *state);

    State<T> *GetState(T data) const;

    State<T> *PopMin();

    bool isExist(const State<T> *state) const;

    bool empty() const { return _sorted_elements.empty(); }

    int size() const;

    void print() const;

    void clear();
};

template<class T>
void StatePriQue<T>::Push(State<T> *state) {
    if (!isExist(state)) {
        T t = state->GetData();
        _elements[t] = _sorted_elements.insert(state);
    }
}

template<class T>
bool StatePriQue<T>::isExist(const State<T> *state) const {
    bool result = _elements.find(state->GetData()) != _elements.end();
    return result;
}

template<class T>
int StatePriQue<T>::size() const {
    return (int) _elements.size();
}

template<class T>
void StatePriQue<T>::Remove(State<T> *state) {
    _sorted_elements.erase(_elements[state->GetData()]);
    _elements.erase(state->GetData());
}

template<class T>
State<T> *StatePriQue<T>::PopMin() {
    State<T> *min = *_sorted_elements.begin();
    Remove(min);
    return min;
}

template<class T>
void StatePriQue<T>::Update(State<T> *state) {
    if (isExist(state)) {
        Remove(state);
        Push(state);
    }
}

template<class T>
State<T> *StatePriQue<T>::GetState(T data) const {
    return *(_elements.at(data));
}

template<class T>
void StatePriQue<T>::print() const {
    for (State<T> *t : _sorted_elements) {
        std::cout << *t << std::endl;
    }
    std::cout << std::endl;
}

template<class T>
void StatePriQue<T>::clear() {
    for (State<T> *state : _sorted_elements) {
        _elements.erase(state->GetData());
        _sorted_elements.erase(state);
        delete state;
    }
}


#endif
