//
// Created by tomme on 04/01/2019.
//

#ifndef AP_SECONDMS_SOLVER_H
#define AP_SECONDMS_SOLVER_H

using namespace std;
template <class Problem, class Solution> class Solver {

public:
    virtual Solution solve(Problem problem) = 0;
};


#endif //AP_SECONDMS_SOLVER_H
