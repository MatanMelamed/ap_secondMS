#ifndef AP_SECONDMS_BFS_H
#define AP_SECONDMS_BFS_H

#include "Searcher.h"
#include "PStatePriQue.h"
#include "PStateUnorderedSet.h"

#include <unordered_set>

template<class T>
class BFS : public Searcher<T> {

public:
    std::vector<State<T> *> Search(Searchable<T> *s) override;

    int SetAnswerAndReset(std::vector<State<T> *> &result,
                          PStatePriQue<T> &open,
                          PStateUnorderedSet<T> &close,
                          State<T> *goal);
};

template<class T>
int BFS<T>::SetAnswerAndReset(std::vector<State<T> *> &result,
                              PStatePriQue<T> &open,
                              PStateUnorderedSet<T> &close,
                              State<T> *goal) {
    int counter = 0;
    State<T> *iterator = goal;
    while (iterator->GetCameFrom() != nullptr) { // last element is dummy
        result.push_back(iterator);
        if (open.isExist(iterator)) { open.Remove(iterator); }
        if (close.isExist(iterator)) { close.Remove(iterator); }
        iterator = iterator->GetCameFrom();
        ++counter;
    }
    counter += open.size() + close.size();

    // delete left memory
    delete iterator; // points to dummy - before the start state.
    open.clear();
    close.clear();

    return counter;
}

template<class T>
std::vector<State<T> *> BFS<T>::Search(Searchable<T> *s) {
    std::vector<State<T> *> result;
    PStatePriQue<T> open;
    PStateUnorderedSet<T> close;

    open.Push(s->GetInitialState());

    while (!open.empty()) {
        State<T> *current = open.PopMin();
        close.Insert(current);
        if (s->isGoal(current)) {
            int devNodes = SetAnswerAndReset(result, open, close, current);
            State<T> *devNodesIndicator = s->GetDummyy();
            devNodesIndicator->SetCost(devNodes);
            result.push_back(devNodesIndicator);
            break;
        }
        std::vector<State<T> *> neighbors = s->GetReachable(current);
        for (State<T> *neighbor : neighbors) {
            if (!close.isExist(neighbor) && !open.isExist(neighbor)) {
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
                State<T> *oldNeighbor = close.GetState(neighbor);
                if (oldNeighbor->GetCost() > neighbor->GetCost()) {
                    close.Remove(neighbor);  // removes old neighbor - same data
                    open.Push(neighbor);
                    neighbor = nullptr;
                }
            }
            if (neighbor != nullptr) {
                delete neighbor;
            }
        }
    }

    return result;
}


#endif
