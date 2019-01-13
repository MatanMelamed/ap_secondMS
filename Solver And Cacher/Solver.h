#ifndef AP_SECONDMS_SOLVER_H
#define AP_SECONDMS_SOLVER_H

using namespace std;

template<class Problem, class Solution>
class Solver {

public:
    virtual Solution solve(Problem problem) = 0;

    virtual Solver *Clone() = 0;
};


#endif
