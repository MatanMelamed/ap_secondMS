//
// Created by tomme on 04/01/2019.
//

#ifndef AP_SECONDMS_CACHEMANAGER_H
#define AP_SECONDMS_CACHEMANAGER_H


template <class Problem, class Solution> class CacheManager {

public:
    virtual bool IsSolutionExists(Problem problem) = 0;
    virtual Solution GetSolution(Problem problem) = 0;
    virtual void SaveSolution(Solution problem) = 0;
};


#endif //AP_SECONDMS_CACHEMANAGER_H
