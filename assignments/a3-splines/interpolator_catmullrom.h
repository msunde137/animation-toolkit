#ifndef _interpolator_catmullrom_
#define _interpolator_catmullrom_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Catmull-Rom 
//--------------------------------

class InterpolatorCatmullRom : public Interpolator
{
public:
    InterpolatorCatmullRom() : Interpolator("Catmull-Rom") {}

    virtual glm::vec3 interpolate(int segment, double u) const {
       // todo: your code here
       // see: interpolator.h and writeup for details
       return glm::vec3(0);
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       // todo: your code here
       // see: interpolator.h and writeup for details
    }
};

#endif
