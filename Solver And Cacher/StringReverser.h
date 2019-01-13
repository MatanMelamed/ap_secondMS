#ifndef AP_SECONDMS_STRINGREVERSER_H
#define AP_SECONDMS_STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include <iostream>
#include <algorithm>

class StringReverser : public Solver<string,string>{
public:
    StringReverser(){}
    string solve(string problem) override;
    ~StringReverser();

};

#endif
