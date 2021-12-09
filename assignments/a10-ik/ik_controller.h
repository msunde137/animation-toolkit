#ifndef IKController_H_
#define IKController_H_

#include "atk/toolkit.h"

class IKController
{
public:
    static bool solveIKAnalytic(atk::Skeleton& skeleton, 
        int jointid, const glm::vec3& goalPos, float epsilon = 0.0001f);

    static bool solveIKCCD(atk::Skeleton& skeleton, 
        int jointid, const glm::vec3& goalPos, 
        const std::vector<atk::Joint*>& chain, float threshold = 10.0, 
        int maxIters = 50, float nudgeFactor = 0.1); 
};

#endif
