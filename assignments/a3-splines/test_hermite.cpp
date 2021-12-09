#include <vector>
#include <iostream>
#include "interpolator_hermite.h"
using namespace glm;
using namespace std;

int main()
{
   std::vector<vec3> keys;
   keys.push_back(vec3(0,0,0));
   keys.push_back(vec3(1,2,0));
   keys.push_back(vec3(3,3,0));
   keys.push_back(vec3(6,3,0));
   keys.push_back(vec3(8,0,0));

   InterpolatorHermite hermite;
   hermite.computeControlPoints(keys);

   // todo: print the control points in hemite
   // verify they match the example from class!
   for (int i = 0; i < hermite.getNumControlPoints(); i++)
   {
      std::cout << "control point: " << to_string(hermite.getControlPoint(i)) << std::endl;
   }

   // test interpolation with clamped endpoints
   hermite.setClamped(true);
   hermite.setClampedDirection(vec3(1.0, 0.0, 0.0));
   hermite.computeControlPoints(keys);

   vec3 value;
   value = hermite.interpolate(0, 0.0);
   std::cout << "(clamped) interpolate(0, 0) = " << to_string(value) << std::endl;

   value = hermite.interpolate(3, 1.0);
   std::cout << "(clamped) interpolate(3, 1) = " << to_string(value) << std::endl;

   value = hermite.interpolate(2, 0.5);
   std::cout << "(clamped) interpolate(2, 0.5) = " << to_string(value) << std::endl;

   // test interpolation with natual endpoints
   hermite.setClamped(false);
   hermite.computeControlPoints(keys);

   value = hermite.interpolate(0, 0.1);
   std::cout << "(natural) interpolate(0, 0) = " << to_string(value) << std::endl;

   value = hermite.interpolate(3, 0.9);
   std::cout << "(natural) interpolate(3, 1) = " << to_string(value) << std::endl;

   value = hermite.interpolate(2, 0.5);
   std::cout << "(natural) interpolate(2, 0.5) = " << to_string(value) << std::endl;
}

