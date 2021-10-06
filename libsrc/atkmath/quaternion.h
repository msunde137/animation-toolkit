#ifndef ATKMATH_QUATERNION_H_
#define ATKMATH_QUATERNION_H_

#include <iostream>
#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {
class Quaternion
{
public:

    // Constructors
    Quaternion();
    Quaternion(double x, double y, double z, double w);
    Quaternion(const Matrix3& m);
    Quaternion(const Vector3& axis, double rad);
    Quaternion(const Quaternion& q);

    // Static functions
    static double Dot(const Quaternion& q0, const Quaternion& q1);
    static Quaternion Slerp(const Quaternion& q0, 
        const Quaternion& q1, double t);

    // Conversion functions
    void toAxisAngle (Vector3& axis, double& angleRad) const;
    void fromAxisAngle (const Vector3& axis, double angleRad);

    Matrix3 toMatrix () const;
    void fromMatrix (const Matrix3& rot);

    // Assignment operators
    Quaternion& operator = (const Quaternion& q);	
    Quaternion& operator += (const Quaternion& q);
    Quaternion& operator -= (const Quaternion& q);
    Quaternion& operator *= (const Quaternion& q);
    Quaternion& operator *= (double d);
    Quaternion& operator /= (double d);

    // Indexing
    double w() const;
    double x() const;
    double y() const;
    double z() const;
    double& operator[](int i); 
    double operator[](int i) const;

    // Friends
    friend Quaternion operator- (const Quaternion& q);					
    friend Quaternion operator+ (const Quaternion& q0, const Quaternion& q1);
    friend Quaternion operator- (const Quaternion& q0, const Quaternion& q1);
    friend Quaternion operator* (const Quaternion& q, double d);
    friend Vector3 operator* (const Quaternion& q, const Vector3& v);
    friend Quaternion operator* (double d, const Quaternion& q);	
    friend Quaternion operator* (const Quaternion& q0, const Quaternion& q1);
    friend Quaternion operator/ (const Quaternion& q, double d);
    friend bool operator== (const Quaternion& q0, const Quaternion& q1);
    friend bool operator!= (const Quaternion& q0, const Quaternion& q1);

    friend std::istream& operator>> (std::istream& s, Quaternion& v);
    friend std::ostream& operator<< (std::ostream& s, const Quaternion& v);

    // Special functions
    double length() const;
    double sqrLength() const;
    void normalize();
    Quaternion normalized() const;
    Quaternion inverse() const;

	// static constants
	static Quaternion Zero;
	static Quaternion Identity;

private:

    union
	 {
	 	 struct
	 	 {
			 double mX;
			 double mY;
			 double mZ;
			 double mW;
		 };
	 	 double mV[4];
	 };
};

}
#endif

