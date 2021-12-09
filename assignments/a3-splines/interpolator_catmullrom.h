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
        if (u < 0 || u > 1 || mCtrlPoints.size() < segment + 4) return glm::vec3(0);
        //if (segment > 0) __debugbreak();
        glm::vec3 cp1 = mCtrlPoints[segment * 4 - segment];
        glm::vec3 cp2 = mCtrlPoints[segment * 4 + 1 - segment];
        glm::vec3 cp3 = mCtrlPoints[segment * 4 + 2 - segment];
        glm::vec3 cp4 = mCtrlPoints[segment * 4 + 3 - segment];

        // function p(t)
        auto p = [cp1, cp2, cp3, cp4](float t) {
            return (float)pow((1 - t), 3) * cp1 + 3 * t * (float)pow((1 - t), 2) * cp2 + 3 * (float)pow(t, 2) * (1 - t) * cp3 + (float)pow(t, 3) * cp4;
        };

        return p(u);
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys)
    {
        if (keys.size() < 2)
        {
            mCtrlPoints = keys;
            return;
        }
        clearControlPoints();

        mCtrlPoints.push_back(keys[0]);
        mCtrlPoints.push_back(keys[0] + (1.0f / 6.0f) * (keys[1] - keys[0]));

        int i = 1;
        for (; i < keys.size() - 1; i++)
        {
            glm::vec3 cp = keys[i] - (1.0f / 6.0f) * (keys[i + 1] - keys[i - 1]);
            mCtrlPoints.push_back(cp);
            mCtrlPoints.push_back(keys[i]);
            mCtrlPoints.push_back(keys[i] * 2.0f - cp);
        }

        mCtrlPoints.push_back(keys[i] - (1.0f / 6.0f) * (keys[i] - keys[i - 1]));
        mCtrlPoints.push_back(keys[i]);
    }
};

#endif