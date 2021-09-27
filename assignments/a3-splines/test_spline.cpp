#include "spline.h"
#include "interpolator_hermite.h"
#include "interpolator_catmullrom.h"
#include "interpolator_linear.h"
#include <iostream>
#include <vector>

using namespace glm;

int main() {
   InterpolatorLinear linear;
   InterpolatorCatmullRom catmullrom;
   InterpolatorHermite hermite;
   hermite.setClamped(true);
   hermite.setClampedDirection(vec3(1,0,0));

   Spline spline;
   spline.addInterpolationType("Linear", &linear);
   spline.addInterpolationType("Hermite", &hermite);
   spline.addInterpolationType("CatmullRom", &catmullrom);

   spline.setInterpolationType("Linear");

   // test with empty values
   std::cout << "\n-------------------------------\n";
   vec3 test;
   test = spline.getValue(0);
   std::cout << "Current interpolation type: " << spline.getInterpolationType() << std::endl;
   std::cout << "Number of control points: " << spline.getNumControlPoints() << std::endl;
   std::cout << "Duration: " << spline.getDuration() << std::endl;
   std::cout << "getValue(0): " << to_string(test) << std::endl;

   // test with 2 values
   std::cout << "\n-------------------------------\n";
   std::cout << "Current interpolation type: " << spline.getInterpolationType() << std::endl;
   spline.appendKey(0, vec3(0.0, 0.0, 0.0));
   spline.appendKey(1, vec3(1.0, 1.0, 0.0));

   test = spline.getValue(-1); // test out of range
   std::cout << "Number of control points: " << spline.getNumControlPoints() << std::endl;
   std::cout << "Duration: " << spline.getDuration() << std::endl;
   std::cout << "getValue(-1): " << to_string(test) << std::endl;

   test = spline.getValue(5); // test out of range
   std::cout << "getValue(5): " << to_string(test) << std::endl;

   test = spline.getValue(0.5);
   std::cout << "getValue(0.5): " << to_string(test) << std::endl;

   test = spline.getValue(0);
   std::cout << "getValue(0): " << to_string(test) << std::endl;

   test = spline.getValue(1);
   std::cout << "getValue(1): " << to_string(test) << std::endl;

   // test with 3 values (with different interpolators)
   spline.appendKey(2, vec3(2,0,0));
   std::cout << "\n-------------------------------\n";
   test = spline.getValue(1.5);
   std::cout << "Current interpolation type: " << spline.getInterpolationType() << std::endl;
   std::cout << "Number of control points: " << spline.getNumControlPoints() << std::endl;
   std::cout << "Duration: " << spline.getDuration() << std::endl;
   std::cout << "getValue(1.5): " << to_string(test) << std::endl;

   spline.setInterpolationType("CatmullRom");
   test = spline.getValue(1.5);
   std::cout << "\n-------------------------------\n";
   std::cout << "Current interpolation type: " << spline.getInterpolationType() << std::endl;
   std::cout << "Number of control points: " << spline.getNumControlPoints() << std::endl;
   std::cout << "Duration: " << spline.getDuration() << std::endl;
   std::cout << "getValue(1.5): " << to_string(test) << std::endl;

   spline.setInterpolationType("Hermite");
   test = spline.getValue(1.5);
   std::cout << "\n-------------------------------\n";
   std::cout << "Current interpolation type: " << spline.getInterpolationType() << std::endl;
   std::cout << "Number of control points: " << spline.getNumControlPoints() << std::endl;
   std::cout << "Duration: " << spline.getDuration() << std::endl;
   std::cout << "getValue(1.5): (clamped) " << to_string(test) << std::endl;

   hermite.setClamped(false);
   spline.computeControlPoints();
   test = spline.getValue(1.5);
   std::cout << "getValue(1.5): (natural) " << to_string(test) << std::endl;

   // test other methods
   spline.editKey(2, vec3(3, 1, 0));
   test = spline.getValue(1.5);
   float duration = spline.getDuration();
   std::cout << "\n-------------------------------\n";
   std::cout << "Current interpolation type: " << spline.getInterpolationType() << std::endl;
   std::cout << "Number of control points: " << spline.getNumControlPoints() << std::endl;
   std::cout << "Duration: " << duration << std::endl;
   std::cout << "getValue(1.5): (natural)" << to_string(test) << std::endl;

   spline.deleteKey(1);
   test = spline.getValue(1.5);
   std::cout << "\n-------------------------------\n";
   std::cout << "Current interpolation type: " << spline.getInterpolationType() << std::endl;
   std::cout << "Number of control points: " << spline.getNumControlPoints() << std::endl;
   std::cout << "Duration: " << duration << std::endl;
   std::cout << "getValue(1.5): " << to_string(test) << std::endl;
}

