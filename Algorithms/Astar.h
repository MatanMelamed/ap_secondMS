#ifndef AP_SECONDMS_ASTAR_H
#define AP_SECONDMS_ASTAR_H

#include <unordered_map>
#include <unordered_set>
#include "SearcherHeuristic.h"
#include "AStarPriQue.h"

template<typename T>
class Astar : public SearcherHeuristic<T> {
protected:
    AStarPriQue<T> open;
    std::unordered_set<State<T> *, PStateHash<T>, PStateComp<T>> close;
    State<T> *_goal;

    bool IsNew(State<T> *state);

    std::vector<State<T> *> GetResults(Searchable<T> *s);

public:
    Astar() : _goal(nullptr) {};

    std::vector<State<T> *> Search(SearchableHeuristic<T> *s) override;
};


template<typename T>
std::vector<State<T> *> Astar<T>::Search(SearchableHeuristic<T> *s) {

    // Get and Set initial state
    State<T> *startState = s->GetInitialState();
    double startHeuristic = s->GetHeuristic(startState);
    open.Push(AStarState<T>({startHeuristic + startState->GetCost(),
                             startHeuristic,
                             startState}));
    // iterate
    while (!open.empty()) {
        State<T> *current = open.PopMin();
        if (s->isGoal(current)) {
            _goal = current;
            break;
        }
        std::vector<std::pair<double, State<T> *>> neighbors =
                s->GetReachableNHeuristic(current);
        for (std::pair<double, State<T> *> neighbor : neighbors) {
            if (IsNew(neighbor.second)) {
                open.Push(AStarState<T>({neighbor.first +
                                         neighbor.second->GetCost(),
                                         neighbor.first,
                                         neighbor.second}));
            } else if (open.isExist(neighbor.second)) {
                State<T> *oldNeighbor = open.GetState(neighbor.second);
                if (oldNeighbor->GetCost() > neighbor.second->GetCost()) {
                    open.Update(neighbor.second);
                }
            }
        }

        close.insert(current);
    }

    return GetResults(s);
}

template<typename T>
std::vector<State<T> *> Astar<T>::GetResults(Searchable<T> *s) {

    int developedNodes = 0;
    std::vector<State<T> *> results;

    State<T> *iterator = _goal;
    while (iterator != nullptr) {
        results.push_back(iterator);
        if (close.find(iterator) != close.end()) {
            close.erase(iterator);
        } else if (open.isExist(iterator)) {
            open.Remove(iterator);
        }
        iterator = iterator->GetCameFrom();
        ++developedNodes;
    }

    developedNodes += open.size() + close.size();
    if (!open.empty()) {
        open.clear();
    }
    if(!close.empty()){
        for (State<T> * state : close) {
            delete state;
        }
        close.clear();
    }

    State<T> *devIndicatorState = s->GetDummy();
    devIndicatorState->SetCost(developedNodes);
    results.push_back(devIndicatorState);

    _goal = nullptr;

    return results;
}

template<typename T>
inline bool Astar<T>::IsNew(State<T> *state) {
    return (!open.isExist(state)) &&                        // not in open
           (close.find(state) == close.end());   // not it close
}

#endif
