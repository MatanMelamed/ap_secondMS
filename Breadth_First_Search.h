#ifndef AP_SECONDMS_BREADTH_FIRST_SEARCH_H
#define AP_SECONDMS_BREADTH_FIRST_SEARCH_H

#include "Searcher.h"
#include <map>
#include <queue>
#include <set>

template<class T>
class Breadth_First_Search: public Searcher<T>{

public:
    std::vector<State<T>*> Search(Searchable<T> *s) override;
};

template<class T>
std::vector<State<T> *> Breadth_First_Search<T>::Search(Searchable<T> *s) {
    std:: map<State<T>,bool> graySet;
    std:: map<State<T>,State<T>> cameFrom;
    std:: map<State<T>,int> distance;
    std:: queue<State<T>> queue;
    State<T>* source = s->GetInitialState();
    distance[*source] = 0;
    graySet[*source] = true;
    queue.push(*source);
    State<T> state(queue.front());
    while(!queue.empty()) {
        state = queue.front();
        queue.pop();
        if(s->isGoal(&state)){
            break;
        }
        for(State<T>* neighbor : s->GetReachable(&state)){
           if(!(graySet.find(*neighbor) != graySet.end())){
                graySet[*neighbor] = true;
                neighbor->SetCameFrom(&state);
                distance[*neighbor] = distance[state] + 1;
                queue.push(*neighbor);
            }
        }
    }
    std:: vector<State<T>*> path;
    while(state!=*source) {
        //path.push_back(&state);
        //state = state.GetCameFrom();
    }
    //path.push_back(&state);

    return path;
}

#endif
