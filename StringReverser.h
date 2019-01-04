//
// Created by tomme on 04/01/2019.
//

#ifndef AP_SECONDMS_STRINGREVERSER_H
#define AP_SECONDMS_STRINGREVERSER_H

#include "Solver.h"
#include <string>
using namespace std;

class StringReverser : public Solver<class Problem,class Solution>{

public:
    string solve(string problem);
    ~StringReverser();

};


#endif //AP_SECONDMS_STRINGREVERSER_H
