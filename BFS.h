#ifndef AP_SECONDMS_BFS_H
#define AP_SECONDMS_BFS_H

#include <unordered_set>
#include <queue>

#include "Searcher.h"

template<typename T>
class BFS : public Searcher<T> {

    std::unordered_set<State<T> *, PStateHash<T>, PStateComp<T>> _grays;
    std::unordered_set<State<T> *, PStateHash<T>, PStateComp<T>> _blacks;

    bool IsWhite(State<T> *state);

    std::vector<State<T> *> GetResults(State<T> *goal, Searchable<T> *s);

public:
    std::vector<State<T> *> Search(Searchable<T> *s) override;
};


template<typename T>
std::vector<State<T> *> BFS<T>::Search(Searchable<T> *s) {
    std::queue<State<T> *> queue;
    State<T> *startState = s->GetInitialState();
    _grays.insert(startState);
    queue.push(startState);

    State<T> *goal = nullptr;
    while (!queue.empty()) {
        State<T> *current = queue.front();
        queue.pop();

        if (goal == nullptr && s->isGoal(current)) { goal = current; }

        std::vector<State<T> *> neighbors = s->GetReachable(current);
        for (State<T> *neighbor : neighbors) {
            if (IsWhite(neighbor)) {
                _grays.insert(neighbor);
                queue.push(neighbor);
            }
        }

        _grays.erase(current);
        _blacks.insert(current);
    }

    return GetResults(goal, s);
}

template<typename T>
bool BFS<T>::IsWhite(State<T> *state) {
    bool isGray = _grays.find(state) != _grays.end();
    bool isBlack = _blacks.find(state) != _blacks.end();
    return !(isBlack || isGray);
}

template<typename T>
std::vector<State<T> *> BFS<T>::GetResults(State<T> *goal, Searchable<T> *s) {

    int developedNodes = 0;
    std::vector<State<T> *> results;

    State<T> *iterator = goal;
    while (iterator != nullptr) {
        results.push_back(iterator);
        _blacks.erase(iterator);
        iterator = iterator->GetCameFrom();
        ++developedNodes;
    }

    if (!_blacks.empty()) {
        for (State<T> *state : _blacks) {
            delete state;
            ++developedNodes;
        }
        _blacks.clear();
    }

    State<T> *devIndicatorState = s->GetDummyy();
    devIndicatorState->SetCost(developedNodes);
    results.push_back(devIndicatorState);

    return results;
}

#endif
