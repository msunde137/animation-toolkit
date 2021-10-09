#include "atkmath/vector3.h"
#include <algorithm>
#include <cmath>

namespace atkmath {
const Vector3 Vector3::AxisX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::AxisY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::AxisZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

using namespace std;

Vector3::Vector3() 
{
    mX = 0; mY = 0; mZ = 0; 
}

Vector3::Vector3(double x, double y, double z)
{ 
    mX = x; mY = y; mZ = z; 
}

Vector3::Vector3(const Vector3& v)
{ 
    mX = v[VX]; mY = v[VY]; mZ = v[VZ]; 
}

// ASSIGNMENT OPERATORS

Vector3& Vector3::operator = (const Vector3& v)
{ 
    mV[VX] = v[VX]; mV[VY] = v[VY]; mV[VZ] = v[VZ]; return *this; 
}

Vector3& Vector3::operator += ( const Vector3& v )
{ 
    mV[VX] += v[VX]; mV[VY] += v[VY]; mV[VZ] += v[VZ]; return *this; 
}

Vector3& Vector3::operator -= ( const Vector3& v )
{ 
    mV[VX] -= v[VX]; mV[VY] -= v[VY]; mV[VZ] -= v[VZ]; return *this; 
}

Vector3& Vector3::operator *= ( double d )
{ 
    mV[VX] *= d; mV[VY] *= d; mV[VZ] *= d; return *this; 
}

Vector3& Vector3::operator /= ( double d )
{ 
    double d_inv = 1.0f/d; 
    mV[VX] *= d_inv; mV[VY] *= d_inv; mV[VZ] *= d_inv;
    return *this; 
}

double& Vector3::operator [] ( int i) {
    assert(! (i < VX || i > VZ));
    return mV[i];
}

double Vector3::operator [] ( int i) const {
    assert(! (i < VX || i > VZ));
    return mV[i];
}

double Vector3::x() const
{
	return mX;
}

double Vector3::y() const
{
	return mY;
}

double Vector3::z() const
{
	return mZ;
}

// SPECIAL FUNCTIONS
double Vector3::length() const
{  
    return sqrt(sqrLength()); 
}

double Vector3::sqrLength() const
{  
    return mV[VX]*mV[VX] + mV[VY]*mV[VY] + mV[VZ]*mV[VZ]; 
}

Vector3 Vector3::normalized() const 
{
    double len = length();
	 Vector3 copy = *this;
    if (len > EPSILON) copy /= length(); 
    return copy;
}

void Vector3::normalize() 
{ 
    *this = normalized();
}

Vector3 Vector3::Cross(const Vector3 &left, const Vector3& right)
{
	 double x = left.y() * right.z() - left.z() * right.y();
	 double y = left.z() * right.x() - left.x() * right.z();
	 double z = left.x() * right.y() - left.y() * right.x();
    return Vector3(x,y,z);
}

// FRIENDS
Vector3 operator - (const Vector3& a)
{  
    return Vector3(-a.x() ,-a.y(),-a.z()); 
}

Vector3 operator + (const Vector3& a, const Vector3& b)
{ 
    return Vector3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z()); 
}

Vector3 operator - (const Vector3& a, const Vector3& b)
{ 
    return Vector3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z()); 
}

Vector3 operator * (const Vector3& a, double d)
{ 
    return Vector3(d*a.x(), d*a.y(), d*a.z()); 
}

Vector3 operator * (double d, const Vector3& a)
{ 
    return a*d; 
}

double operator * (const Vector3& a, const Vector3& b)
{ 
    return (a.x()*b.x() + a.y()*b.y() + a.z()*b.z()); 
}

Vector3 operator / (const Vector3& a, double d)
{ 
    double d_inv = 1.0/d; 
    return Vector3(a.x()*d_inv, a.y()*d_inv, a.z()*d_inv); 
}


int operator == (const Vector3& a, const Vector3& b)
{ 
    float eps = 0.001f; // low precision equality
    return (fabs(a.x() - b.x()) < eps && 
            fabs(a.y() - b.y()) < eps && 
            fabs(a.z() - b.z()) < eps);
}

int operator != (const Vector3& a, const Vector3& b)
{ 
    return !(a == b); 
}

double Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return a[VX]*b[VX] + a[VY]*b[VY] + a[VZ]*b[VZ];
}

std::istream& operator>>(std::istream& s, Vector3& v)
{
    double x, y, z;
    s >> x >> y >> z;
    v = Vector3(x, y, z);
    return s;
}

std::ostream& operator<<(std::ostream& s, const Vector3& v)
{
    s << (float) v[VX] << " " << (float) v[VY] << " " << (float) v[VZ];
    return s;
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
    return a * (1-t) + b * t;
}

double Vector3::Distance(const Vector3& a, const Vector3& b)
{
    return sqrt(DistanceSqr(a,b));
}

double Vector3::DistanceSqr(const Vector3& a, const Vector3& b)
{
    return (a[0]-b[0])*(a[0]-b[0]) + 
           (a[1]-b[1])*(a[1]-b[1]) + 
           (a[2]-b[2])*(a[2]-b[2]);
}
}