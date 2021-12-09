#include <iostream>
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"

using atkmath::Quaternion;
using atkmath::Vector3;

int main(int argc, char** argv)
{
   Quaternion q0(Vector3(0,0,1), 0 * atkmath::Deg2Rad);
   Quaternion q1(Vector3(0,0,1), 120 * atkmath::Deg2Rad);

   std::cout << "q0 " << q0 << std::endl;
   std::cout << "q1 " << q1 << std::endl;

   Quaternion q;
   for (float t = 0.25; t <= 1.0; t += 0.25) {
      q = Quaternion::Slerp(q0, q1, t);
      std::cout << "t=" << t << ": " << q << std::endl;
   }
}

