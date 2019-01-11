#ifndef AP_SECONDMS_BFS_H
#define AP_SECONDMS_BFS_H

#include "Searcher.h"
#include "StatePriQue.h"

#include <unordered_set>

template<class T>
class BFS : public Searcher<T> {

public:
    std::vector<State<T> *> Search(Searchable<T> *s) override;

    int SetAnswerAndReset(std::vector<State<T> *> &result,
                          StatePriQue<T> &open,
                          std::unordered_set<State<T> *> &close,
                          State<T> *goal);
};

template<class T>
int BFS<T>::SetAnswerAndReset(std::vector<State<T> *> &result,
                              StatePriQue<T> &open,
                              std::unordered_set<State<T> *> &close,
                              State<T> *goal) {
    int counter = 0;
    State<T> *iterator = goal;
    while (iterator->GetCameFrom() != nullptr) { // last element is dummy
        result.push_back(iterator);
        if (open.isExist(iterator)) {
            open.Remove(iterator);
        }
        if (close.find(iterator) != close.end()) {
            close.erase(iterator);
        }
        iterator = iterator->GetCameFrom();
        ++counter;
    }
    counter += open.size() + close.size();

    // delete memory
    delete iterator; // points to dummy - before the start state.
    open.clear();
    for(State<T> * state: close){
        delete state;
    }
    close.clear();

    return counter;
}

template<class T>
std::vector<State<T> *> BFS<T>::Search(Searchable<T> *s) {
    std::vector<State<T> *> result;
    StatePriQue<T> open;
    open.Push(s->GetInitialState());
    std::unordered_set<State<T> *> close;
    while (!open.empty()) {
        State<T> *current = open.PopMin();
        close.insert(current);
        if (s->isGoal(current)) {
            int devNodes = SetAnswerAndReset(result, open, close, current);
            auto *devNodesIndicator = new State<T>({-1, -1}, devNodes);
            result.push_back(devNodesIndicator);
            break;
        }
        std::vector<State<T> *> neighbors = s->GetReachable(current);
        for (State<T> *neighbor : neighbors) {
            if (!(close.find(neighbor) != close.end()) &&
                !open.isExist(neighbor)) {
                neighbor->SetCameFrom(current);
                open.Push(neighbor);
                neighbor = nullptr;
            } else if (open.isExist(neighbor)) {
                State<T> *oldNeighbor = open.GetState(neighbor->GetData());
                if (oldNeighbor->GetCost() > neighbor->GetCost()) {
                    open.Update(neighbor);
                    neighbor = nullptr;
                }
            } else { // State must be in close.
                State<T> *oldNeighbor = *(close.find(neighbor));
                close.erase(oldNeighbor);
                open.Push(neighbor);
                neighbor = nullptr;
            }
            if (neighbor != nullptr) {
                delete neighbor;
            }
        }
    }

    return result;
}


#endif
