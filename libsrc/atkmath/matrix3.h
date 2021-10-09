#ifndef ATKMATH_MATRIX3_H_
#define ATKMATH_MATRIX3_H_

#include <iostream>
#include "agl/aglm.h"
#include "atkmath/vector3.h"

namespace atkmath {
class Quaternion;
class Matrix3
{
public:

    // Constructors
    Matrix3();
    Matrix3(double a11, double a12, double a13,
             double a21, double a22, double a23,
             double a31, double a32, double a33);
    Matrix3(const Matrix3& m);
    Matrix3(const Vector3& axis, double angleRad);
    Matrix3(const Quaternion& q);

    enum RotOrder { XYZ, XZY, YXZ, YZX, ZXY, ZYX };
    Matrix3(RotOrder roo, const Vector3& eulerRad);

    // Static functions
    static Matrix3 Identity;
    static Matrix3 Zero;

   // Conversion with euler angles
    Vector3 toEulerAngles(RotOrder roo) const;
    Vector3 toEulerAnglesXYZ() const;
    Vector3 toEulerAnglesXZY() const;
    Vector3 toEulerAnglesYXZ() const;
    Vector3 toEulerAnglesYZX() const;
    Vector3 toEulerAnglesZXY() const;
    Vector3 toEulerAnglesZYX() const;
    void fromEulerAngles(RotOrder roo, const Vector3& anglesRad);
    void fromEulerAnglesXYZ(const Vector3& anglesRad);
    void fromEulerAnglesXZY(const Vector3& anglesRad);
    void fromEulerAnglesYXZ(const Vector3& anglesRad);
    void fromEulerAnglesYZX(const Vector3& anglesRad);
    void fromEulerAnglesZXY(const Vector3& anglesRad);
    void fromEulerAnglesZYX(const Vector3& anglesRad);

   void fromAxisAngle(const Vector3& axis, double rad);
   void toAxisAngle(Vector3& axis, double& rad) const;

    // Conversion with Quaternion
    Quaternion toQuaternion() const;
    void fromQuaternion(const Quaternion& q);

    // Assignment operators
    Matrix3& operator = ( const Matrix3& m );     // assignment of a mat3
    Matrix3& operator += ( const Matrix3& m );      // incrementation by a mat3
    Matrix3& operator -= ( const Matrix3& m );      // decrementation by a mat3
    Matrix3& operator *= ( double d );      // multiplication by a constant
    Matrix3& operator /= ( double d );      // division by a constant
    double* operator [] (int i);          // indexing
    const double* operator [] ( int i) const;   // read-only indexing

    // special functions
    Matrix3 transpose() const;
    void writeToGLMatrix(float* m) const;
    glm::mat4 writeToMat4() const;
    void readFromGLMatrix(float* m);

    // friends
    friend Matrix3 operator - (const Matrix3& a);           // -m1
    friend Matrix3 operator + (const Matrix3& a, const Matrix3& b);     // m1 + m2
    friend Matrix3 operator - (const Matrix3& a, const Matrix3& b);     // m1 - m2
    friend Matrix3 operator * (const Matrix3& a, const Matrix3& b);   // m1 * m2
    friend Matrix3 operator * (const Matrix3& a, double d);     // m1 * 3.0
    friend Matrix3 operator * (double d, const Matrix3& a);     // 3.0 * m1
    friend Matrix3 operator / (const Matrix3& a, double d);     // m1 / 3.0
    friend int operator == (const Matrix3& a, const Matrix3& b);      // m1 == m2 ?
    friend int operator != (const Matrix3& a, const Matrix3& b);      // m1 != m2 ?

    friend std::istream& operator >> (std::istream& s, Matrix3& v);
    friend std::ostream& operator << (std::ostream& s, const Matrix3& v);

    friend Vector3 operator * (const Matrix3& a, const Vector3& v);     // linear transform
    friend Matrix3 operator * (const Matrix3& a, const Matrix3& b); // matrix 3 product

private:
   union
   {
     struct
      {
         double m11;
         double m12;
         double m13;
         double m21;
         double m22;
         double m23;
         double m31;
         double m32;
         double m33;
      };
     double mM[3][3];
   };
};

}

#endif

