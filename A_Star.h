//
// Created by tomme on 11/01/2019.
//

#ifndef AP_SECONDMS_A_STAR_H
#define AP_SECONDMS_A_STAR_H

#include "Searcher.h"
template<class T>
class A_Star: public Searcher<T>{
public:
    std::vector<State<T>> Search(Searchable<T> *s) override;
};
template<class T>
std::vector<State<T>> A_Star<T>::Search(Searchable<T> *s){

}

#endif //AP_SECONDMS_A_STAR_H
