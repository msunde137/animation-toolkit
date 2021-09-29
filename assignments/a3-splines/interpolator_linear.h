#ifndef _interpolator_linear_H_
#define _interpolator_linear_H_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Linear 
//--------------------------------

class InterpolatorLinear : public Interpolator
{
public:
    InterpolatorLinear() : Interpolator("Linear") {}
    virtual glm::vec3 interpolate(int segment, double u) const
    {
        if (u < 0 || u > 1 || mCtrlPoints.size() <= segment + 1) return glm::vec3(0);
        return (1.0f - (float)u) * mCtrlPoints[segment] + (float)u * mCtrlPoints[segment + 1];
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
        mCtrlPoints = keys;
    }
};

#endif
