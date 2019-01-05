//
// Created by tomme on 04/01/2019.
//

#ifndef AP_SECONDMS_FILECACHEMANAGER_H
#define AP_SECONDMS_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <string>

template<class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem,Solution> {

public:
    bool IsSolutionExists(Problem problem);

    Solution GetSolution(Problem problem);

    void SaveSolution(Solution solution);
};


#endif //AP_SECONDMS_FILECACHEMANAGER_H
