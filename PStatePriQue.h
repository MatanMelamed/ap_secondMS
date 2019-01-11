#ifndef AP_SECONDMS_CUSTOMQUEUE_H
#define AP_SECONDMS_CUSTOMQUEUE_H

#include <iostream>
#include <set>
#include <unordered_map>

#include "State.h"


template<class T>
class PStatePriQue {
    std::unordered_map<T,
            typename std::multiset<State<T> *>::iterator> _elements;
    std::multiset<State<T> *, PStateComp<T>> _sorted_elements;
public:
    PStatePriQue() = default;

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
void PStatePriQue<T>::Push(State<T> *state) {
    if (!isExist(state)) {
        T t = state->GetData();
        _elements[t] = _sorted_elements.insert(state);
    }
}

template<class T>
bool PStatePriQue<T>::isExist(const State<T> *state) const {
    bool result = _elements.find(state->GetData()) != _elements.end();
    return result;
}

template<class T>
int PStatePriQue<T>::size() const {
    return (int) _elements.size();
}

template<class T>
void PStatePriQue<T>::Remove(State<T> *state) {
    _sorted_elements.erase(_elements[state->GetData()]);
    _elements.erase(state->GetData());
}

template<class T>
State<T> *PStatePriQue<T>::PopMin() {
    State<T> *min = *_sorted_elements.begin();
    Remove(min);
    return min;
}

template<class T>
void PStatePriQue<T>::Update(State<T> *state) {
    if (isExist(state)) {
        Remove(state);
        Push(state);
    }
}

template<class T>
State<T> *PStatePriQue<T>::GetState(T data) const {
    return *(_elements.at(data));
}

template<class T>
void PStatePriQue<T>::print() const {
    for (State<T> *t : _sorted_elements) {
        std::cout << *t << std::endl;
    }
    std::cout << std::endl;
}

template<class T>
void PStatePriQue<T>::clear() {
    for (State<T> *state : _sorted_elements) {
        _elements.erase(state->GetData());
        _sorted_elements.erase(state);
        delete state;
    }
}


#endif
