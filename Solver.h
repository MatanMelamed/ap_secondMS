//
// Created by tomme on 04/01/2019.
//

#ifndef AP_SECONDMS_SOLVER_H
#define AP_SECONDMS_SOLVER_H


template <class Problem, class Solution> class Solver {

public:
    Solution solve(Problem problem);
};


#endif //AP_SECONDMS_SOLVER_H
