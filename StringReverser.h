//
// Created by tomme on 04/01/2019.
//

#ifndef AP_SECONDMS_STRINGREVERSER_H
#define AP_SECONDMS_STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include <iostream>
using namespace std;

class StringReverser : public Solver<string,string>{
public:
    StringReverser(){}
    string solve(string problem) override;
    ~StringReverser();

};


#endif //AP_SECONDMS_STRINGREVERSER_H
