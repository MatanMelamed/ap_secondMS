//
// Created by tomme on 04/01/2019.
//

#ifndef AP_SECONDMS_CACHEMANAGER_H
#define AP_SECONDMS_CACHEMANAGER_H

#include "Solver.h"

template <class Solution, class Problem> class CacheManager :
        public Solver<class S, class P> {
    bool IsSolutionExists(Problem p);
    Solution GetSolution(Problem p);
    void SaveSolution(Solution s);
};


#endif //AP_SECONDMS_CACHEMANAGER_H
