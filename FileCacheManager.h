//
// Created by tomme on 04/01/2019.
//

#ifndef AP_SECONDMS_FILECACHEMANAGER_H
#define AP_SECONDMS_FILECACHEMANAGER_H

#include "CacheManager.h"

class FileCacheManager: public CacheManager<class Solution,class Problem> {
    bool IsSolutionExists(Problem p);
    Solution GetSolution(Problem p);
    void SaveSolution(Solution s);
};


#endif //AP_SECONDMS_FILECACHEMANAGER_H
