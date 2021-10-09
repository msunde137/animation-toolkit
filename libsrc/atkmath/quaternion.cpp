#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include <algorithm>
#include <cmath>

using namespace std;

namespace atkmath {

Quaternion Quaternion::Zero;
Quaternion Quaternion::Identity(0,0,0,1);

Quaternion::Quaternion()
{
    mW = 0; mX = 0; mY = 0; mZ = 0;
}

Quaternion::Quaternion(double x, double y, double z, double w)
{
    mW = w; mX = x; mY = y; mZ = z;
}

Quaternion::Quaternion(const Quaternion& q)
{
    mW = q[VW]; mX = q[VX]; mY = q[VY]; mZ = q[VZ];
}

Quaternion::Quaternion(const Matrix3& m)
{
	 fromMatrix(m);
}

Quaternion::Quaternion(const Vector3& axis, double rad)
{
	 fromAxisAngle(axis, rad);
}


double Quaternion::Dot(const Quaternion& q0, const Quaternion& q1)
{
    return q0[VW] * q1[VW] + q0[VX] * q1[VX] + q0[VY] * q1[VY] + q0[VZ] * q1[VZ];
}

// Assignment operators
Quaternion& Quaternion::operator = (const Quaternion& q)
{
    mW = q[VW]; mX = q[VX]; mY = q[VY]; mZ = q[VZ];
    return *this;
}

Quaternion& Quaternion::operator += (const Quaternion& q)
{
    mW += q[VW]; mX += q[VX]; mY += q[VY]; mZ += q[VZ];
    return *this;
}

Quaternion& Quaternion::operator -= (const Quaternion& q)
{
    mW -= q[VW]; mX -= q[VX]; mY -= q[VY]; mZ -= q[VZ];
    return *this;
}

Quaternion& Quaternion::operator *= (const Quaternion& q)
{
    *this = Quaternion(
        mW * q[VX] + mX * q[VW] + mY * q[VZ] - mZ * q[VY],
        mW * q[VY] + mY * q[VW] + mZ * q[VX] - mX * q[VZ],
        mW * q[VZ] + mZ * q[VW] + mX * q[VY] - mY * q[VX],
        mW * q[VW] - mX * q[VX] - mY * q[VY] - mZ * q[VZ]);
    return *this;
}

Quaternion& Quaternion::operator *= (double d)
{
    mW *= d; mX *= d; mY *= d; mZ *= d;
    return *this;
}

Quaternion& Quaternion::operator /= (double d)
{
    mW /= d; mX /= d; mY /= d; mZ /= d;
    return *this;
}

// Indexing
double& Quaternion::operator [](int i)
{
    return mV[i];
}

double Quaternion::operator [](int i) const
{
    return mV[i];
}

double Quaternion::w() const
{
    return mW;
}

double Quaternion::x() const
{
    return mX;
}

double Quaternion::y() const
{
    return mY;
}

double Quaternion::z() const
{
    return mZ;
}

// Friends

Quaternion operator - (const Quaternion& q)
{
    return Quaternion(-q[VX], -q[VY], -q[VZ], -q[VW]); 
}

Quaternion operator + (const Quaternion& q0, const Quaternion& q1)
{
    return Quaternion(
			q0[VX] + q1[VX], 
			q0[VY] + q1[VY], 
			q0[VZ] + q1[VZ],
         q0[VW] + q1[VW]); 
}

Quaternion operator - (const Quaternion& q0, const Quaternion& q1)
{
    return Quaternion(
			q0[VX] - q1[VX], 
			q0[VY] - q1[VY], 
			q0[VZ] - q1[VZ],
			q0[VW] - q1[VW]); 
}

Quaternion operator * (const Quaternion& q, double d)
{
    return Quaternion(
			q[VX] * d, 
			q[VY] * d, 
			q[VZ] * d,
			q[VW] * d); 
}

Vector3 operator * (const Quaternion& q, const Vector3& v)
{
    Matrix3 m = q.toMatrix();
    return m * v;
}

Quaternion operator * (double d, const Quaternion& q)
{
    return Quaternion(
			q[VX] * d, 
			q[VY] * d, 
			q[VZ] * d,
			q[VW] * d); 
}

Quaternion operator * (const Quaternion& q0, const Quaternion& q1)
{
    return Quaternion(
        q0[VW] * q1[VX] + q0[VX] * q1[VW] + q0[VY] * q1[VZ] - q0[VZ] * q1[VY],
        q0[VW] * q1[VY] + q0[VY] * q1[VW] + q0[VZ] * q1[VX] - q0[VX] * q1[VZ],
        q0[VW] * q1[VZ] + q0[VZ] * q1[VW] + q0[VX] * q1[VY] - q0[VY] * q1[VX],
        q0[VW] * q1[VW] - q0[VX] * q1[VX] - q0[VY] * q1[VY] - q0[VZ] * q1[VZ]);
}

Quaternion operator / (const Quaternion& q, double d)
{
    return Quaternion(
			q[VX] / d, 
			q[VY] / d, 
			q[VZ] / d,
			q[VW] / d);
}

bool operator == (const Quaternion& q0, const Quaternion& q1)
{
    float eps = 0.001f;
    // check q0 = q1 or q0 = -q1
    return (abs(q0[VW] - q1[VW]) < eps &&
            abs(q0[VX] - q1[VX]) < eps &&
            abs(q0[VY] - q1[VY]) < eps &&
            abs(q0[VZ] - q1[VZ]) < eps)
           ||
           (abs(q0[VW] + q1[VW]) < eps &&
            abs(q0[VX] + q1[VX]) < eps &&
            abs(q0[VY] + q1[VY]) < eps &&
            abs(q0[VZ] + q1[VZ]) < eps);
}

bool operator != (const Quaternion& q0, const Quaternion& q1)
{
    return !(q0 == q1); 
}

// special functions

double Quaternion::sqrLength() const
{
    return mV[VW] * mV[VW] + mV[VX] * mV[VX] + mV[VY] * mV[VY] + mV[VZ] * mV[VZ];
}

double Quaternion::length() const
{
    return sqrt(sqrLength());
}

Quaternion Quaternion::normalized() const
{
	 Quaternion q = *this;
    double l = length();
    if (l > EPSILON)
    {
        q /= l;
    }
	 else
	 {
		  std::cout << "WARNING: Normalize Quaternion with length 0\n";
	 }
	 return q;
}

void Quaternion::normalize()
{
	 Quaternion q = normalized();
    *this = q;
}

Quaternion Quaternion::inverse() const
{
    return Quaternion(-mX, -mY, -mZ, mW) / sqrLength();
}

std::istream& operator >> (std::istream& s, Quaternion& v)
{
    double x, y, z, w;
    s >> w >> x >> y >> z;
    v[VX] = x;
    v[VY] = y;
    v[VZ] = z;
    v[VW] = w;
    return s;
}

std::ostream& operator << (std::ostream& s, const Quaternion& v)
{
    s << (float) v[VX] << " " 
      << (float) v[VY] << " " 
	   << (float) v[VZ] << " "
      << (float) v[VW];
    return s;
}
}