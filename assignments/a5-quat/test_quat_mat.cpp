#include <iostream>
#include <cmath>
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
#include "atkmath/constants.h"

using atkmath::Quaternion;
using atkmath::Matrix3;
using atkmath::Vector3;
using atkmath::Rad2Deg;

int main()
{
    Quaternion q;
    Matrix3 m;

    m.fromEulerAnglesXYZ(Vector3(0,0,M_PI/4));
    q.fromMatrix(m);
    std::cout << "45 Z " << q << std::endl;

    m = q.toMatrix();
    std::cout << "45 Z" << std::endl << m << std::endl;

    m.fromEulerAnglesXYZ(Vector3(0,M_PI/4,0));
    q.fromMatrix(m);
    std::cout << "45 Y " << q << std::endl;

    m = q.toMatrix();
    std::cout << "45 Y " << std::endl << m << std::endl;

    m.fromEulerAnglesXYZ(Vector3(M_PI/4,0,0));
    q.fromMatrix(m);
    std::cout << "45 X " << q << std::endl;

    m = q.toMatrix();
    std::cout << "45 X" << std::endl << m << std::endl;

    return 0;
}
