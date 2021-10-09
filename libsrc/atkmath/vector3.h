// alinen 2017
//
#ifndef ATKMATH_VECTOR_H_
#define ATKMATH_VECTOR_H_

#include <iostream>
#include <assert.h>
#include "atkmath/constants.h"

namespace atkmath {
class Vector3
{
public:
    // Constructors
    Vector3();
    Vector3(double x, double y, double z = 0);
    Vector3(const Vector3& v);			

    // Assignment operators
    Vector3& operator = ( const Vector3& v );	
    Vector3& operator += ( const Vector3& v );
    Vector3& operator -= ( const Vector3& v );
    Vector3& operator *= ( double d );	
    Vector3& operator /= ( double d );

    double& operator [] ( int i);
    double operator[] (int i) const;
    double x() const;
    double y() const;
    double z() const;

    // special functions
    double length() const;				// length of a Vector3
    double sqrLength() const;		   // squared length of a Vector3
    void normalize();					// normalize a Vector3 in place
    Vector3 normalized() const;	   // Returns this vector with length 1

    // friends
    friend  Vector3 operator - (const Vector3& v);
    friend  Vector3 operator + (const Vector3& a, const Vector3& b);
    friend  Vector3 operator - (const Vector3& a, const Vector3& b);
    friend  Vector3 operator * (const Vector3& a, double d);
    friend  Vector3 operator * (double d, const Vector3& a);
    friend  Vector3 operator / (const Vector3& a, double d);
    friend  int operator == (const Vector3& a, const Vector3& b);	
    friend  int operator != (const Vector3& a, const Vector3& b);	

    // input output
    friend std::istream& operator>>(std::istream& s, Vector3& v);
    friend std::ostream& operator<<(std::ostream& s, const Vector3& v);

	 // Constants and static functions
    static const Vector3 AxisX;
    static const Vector3 AxisY;
    static const Vector3 AxisZ;
    static const Vector3 Zero;
    static double Dot(const Vector3& a, const Vector3& b); // dot product
    static double Distance(const Vector3& a, const Vector3& b); 
    static double DistanceSqr(const Vector3& a, const Vector3& b); 
    static Vector3 Cross(const Vector3 &left, const Vector3& right);
    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

private:

    union 
    {
       struct 
       {
           double mX;
           double mY;
           double mZ;
       };
       double mV[3];
    };
};
}
#endif

