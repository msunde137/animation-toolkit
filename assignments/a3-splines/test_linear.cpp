#include "interpolator_linear.h"
#include <iostream>
#include <vector>
using namespace glm;

int main()
{
   std::vector<vec3> keys;
   keys.push_back(vec3(0,0,0));
   keys.push_back(vec3(1,1,0));
   keys.push_back(vec3(2,0,0));

   InterpolatorLinear interp;
   interp.computeControlPoints(keys);

   for (int i = 0; i < interp.getNumControlPoints(); i++)
   {
      std::cout << "control points: " << to_string(interp.getControlPoint(i)) << std::endl;
   }

   vec3 value;
   value = interp.interpolate(0, 0.0);
   std::cout << "interpolate(0, 0) = " << to_string(value) << std::endl;

   value = interp.interpolate(1, 1.0);
   std::cout << "interpolate(1, 1) = " << to_string(value) << std::endl;

   value = interp.interpolate(1, 0.5);
   std::cout << "interpolate(1, 0.5) = " << to_string(value) << std::endl;
}

