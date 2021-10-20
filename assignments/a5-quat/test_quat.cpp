#include <iostream>
#include <cmath>
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"
#include "atkmath/matrix3.h"
#include "atkmath/constants.h"

using atkmath::Quaternion;
using atkmath::Vector3;
using atkmath::Rad2Deg;

int main()
{
    Quaternion q;
    Vector3 v; double angle;

    q.fromAxisAngle(Vector3(0,0,1), M_PI/4);
    q.toAxisAngle(v, angle);
    std::cout << "45 Z " << q << " " << v << " " << angle * Rad2Deg << std::endl;

    q.fromAxisAngle(Vector3(0,1,0), M_PI/4);
    q.toAxisAngle(v, angle);
    std::cout << "45 Y " << q << " " << v << " " << angle * Rad2Deg << std::endl;

    q.fromAxisAngle(Vector3(1,0,0), M_PI/4);
    q.toAxisAngle(v, angle);
    std::cout << "45 X " << q << " " << v << " " << angle * Rad2Deg << std::endl;

    return 0;
}
