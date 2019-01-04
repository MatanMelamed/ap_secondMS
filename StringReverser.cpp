//
// Created by tomme on 04/01/2019.
//

#include "StringReverser.h"


string StringReverser::solve(string problem) {
    string st="";
    for(int i=0;i<problem.length();i++){
        st = problem[i]+st;
    }
    return st;
}