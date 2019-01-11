#ifndef AP_SECONDMS_DFS_H
#define AP_SECONDMS_DFS_H

#include "Searcher.h"
#include <stack>
#include <hash_map>
#include <map>
#include <stack>
#include <set>

template<class T>
class DFS : public Searcher<T>{
private:

public:
    virtual std::vector<State<T>> Search(Searchable<T> *s);
    ~DFS();

};

template<class T>
std::vector<State<T>> DFS<T>::Search(Searchable<T> *s) {
    std:: set<State<T>*> graySet;
    std:: map<State<T>*,State<T>*> cameFrom;
    std:: map<State<T>*,int> distance;
    std:: stack<State<T>*> stack;
    State<T>* source = s->GetInitialState();
    distance[source] = 0;
    stack.push(source);
    while(!stack.empty()) {
        State<T>* state = stack.top();
        stack.pop();
        for(State<T>* neighbor : s->GetReachable(state)){
            if(graySet.count(neighbor)!=1){
                graySet[neighbor];
                cameFrom[neighbor] = state;
                distance[neighbor] = distance[state] + 1;
                stack.push(neighbor);
            }
        }
    }
    return nullptr;
}


#endif
