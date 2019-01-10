#ifndef AP_SECONDMS_BFS_H
#define AP_SECONDMS_BFS_H

#include "Searcher.h"
#include "StatePriQue.h"

#include <unordered_set>

template<class T>
class BFS : public Searcher<T> {

public:
    std::vector<State<T>> Search(Searchable<T> *s) override;
};

template<class T>
std::vector<State<T>> BFS<T>::Search(Searchable<T> *s) {
    StatePriQue<T> open;
    open.Add(&(s->GetInitialState()));
    std::unordered_set<State<T> *> close;
    while (!open.empty()) {
        State<T> *current = open.PopMin();
        close.insert(current);
        if (s->isGoal(current)) {
            //backtrace
        }
        std::vector<State<T> *> neighbors = s->GetReachable(current);
        for (State<T> *neighbor : neighbors) {
            if (!(close.find(neighbor) != close.end()) &&
                !open.IsExists(neighbor)) {
                neighbor->SetCameFrom(current);
                open.Push(neighbor);
                neighbors.erase(neighbor);
                neighbor = nullptr;
            } else if (open.IsExists(neighbor)) {
                State<T> *oldNeighbor = open.GetState(neighbor->GetData());
                if (oldNeighbor->GetCost() > neighbor->GetCost()) {
                    open.Update(neighbor);
                    neighbors.erase(neighbor);
                    neighbor = nullptr;
                }
            } else { // State must be in close.
                State<T> *oldNeighbor = *(close.find(neighbor));
                close.erase(oldNeighbor);
                open.Push(neighbor);
                neighbors.erase(neighbor);
                neighbor = nullptr;
            }
            if (neighbor != nullptr) {
                delete neighbor;
            }
        }
    }

    return std::vector<State<T>>();
}


#endif
