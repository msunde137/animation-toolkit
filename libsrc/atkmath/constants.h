#ifndef ATKMATH_CONSTANTS_H_
#define ATKMATH_CONSTANTS_H_

namespace atkmath {
	
const double PI = 3.1415926535897932384626433832795;
const double PI_2 = 1.5707963267948966192313216916398;

const double EPSILON = 0.000001;
const double Rad2Deg = (180.0f / PI);			// Rad to Degree
const double Deg2Rad = (PI / 180.0f);			// Degree to Rad

template <typename T>
bool IS_ZERO(T x, double eps = 0.001) 
{
	return abs(x) < eps;
}

template <typename T>
int SGN(T x)
{
	return (x >= 0? 1: -1); 
}

enum {VX, VY, VZ, VW};
}

#endif

