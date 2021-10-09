#include "agl/aglm.h"
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

namespace atkmath {
Matrix3 Matrix3::Zero;
Matrix3 Matrix3::Identity(1,0,0, 0,1,0, 0,0,1);

Matrix3::Matrix3() 
{
	 memset(mM, 0, sizeof(double)*9);
}

Matrix3::Matrix3(double a11, double a12, double a13,
                   double a21, double a22, double a23,
                   double a31, double a32, double a33)
{
	 m11 = a11; m12 = a12; m13 = a13;
	 m21 = a21; m22 = a22; m23 = a23;
	 m31 = a31; m32 = a32; m33 = a33;
}

Matrix3::Matrix3(const Matrix3& m)
{ 
	 memcpy(mM, m.mM, sizeof(double)*9);
}

Matrix3::Matrix3(const Quaternion& q)
{ 
	 fromQuaternion(q);
}

Matrix3::Matrix3(Matrix3::RotOrder roo, const Vector3& eulerAngles)
{
	 fromEulerAngles(roo, eulerAngles);
}

Matrix3::Matrix3(const Vector3& axis, double rad)
{
	 fromAxisAngle(axis, rad);
}

Vector3 Matrix3::toEulerAngles(Matrix3::RotOrder roo) const
{
	 switch (roo)
	 {
	 case XYZ: return toEulerAnglesXYZ(); 
	 case XZY: return toEulerAnglesXZY(); 
	 case YXZ: return toEulerAnglesYXZ(); 
	 case YZX: return toEulerAnglesYZX(); 
	 case ZXY: return toEulerAnglesZXY(); 
	 case ZYX: return toEulerAnglesZYX(); 
	 }
	 return Vector3();
}

void Matrix3::fromEulerAngles(Matrix3::RotOrder roo, const Vector3& eulerAngles)
{
	 switch (roo)
	 {
	 case XYZ: fromEulerAnglesXYZ(eulerAngles); break;
	 case XZY: fromEulerAnglesXZY(eulerAngles); break;
	 case YXZ: fromEulerAnglesYXZ(eulerAngles); break;
	 case YZX: fromEulerAnglesYZX(eulerAngles); break;
	 case ZXY: fromEulerAnglesZXY(eulerAngles); break;
	 case ZYX: fromEulerAnglesZYX(eulerAngles); break;
	 }
}

// Conversion with Quaternion
Quaternion Matrix3::toQuaternion() const
{
    Quaternion q;
    q.fromMatrix(*this);
    return q;
}

void Matrix3::fromQuaternion(const Quaternion& q) 
{
    *this = q.toMatrix();
}

// ASSIGNMENT OPERATORS
Matrix3& Matrix3::operator = ( const Matrix3& m )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] = m[i][j]; 
    return *this; 
}

Matrix3& Matrix3::operator += ( const Matrix3& m )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] += m[i][j]; 
    return *this; 
}

Matrix3& Matrix3::operator -= ( const Matrix3& m )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] -= m[i][j]; 
    return *this; 
}

Matrix3& Matrix3::operator *= ( double d )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] *= d; 
    return *this; 
}

Matrix3& Matrix3::operator /= ( double d )
{ 
    for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++) 
		 	   mM[i][j] /= d; 
    return *this; 
}

double* Matrix3::operator [] (int i) 
{
    assert(! (i < 0 || i > 3));
    return mM[i];
}

const double* Matrix3::operator [] (int i) const 
{
    assert(!(i < 0 || i > 3));
    return mM[i];
}

// SPECIAL FUNCTIONS

Matrix3 Matrix3::transpose() const 
{
    return Matrix3(
        mM[0][0], mM[1][0], mM[2][0],
        mM[0][1], mM[1][1], mM[2][1],
        mM[0][2], mM[1][2], mM[2][2]);
}

// FRIENDS
Matrix3 operator - (const Matrix3& a)
{ 
    return Matrix3(-a.m11, -a.m12, -a.m13, 
                    -a.m21, -a.m22, -a.m23,
                    -a.m31, -a.m32, -a.m33);
}

Matrix3 operator + (const Matrix3& a, const Matrix3& b)
{ 
	 Matrix3 result;
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  result[i][j] = a[i][j] + b[i][j];
	 return result;
}

Matrix3 operator - (const Matrix3& a, const Matrix3& b)
{ 
	 Matrix3 result;
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  result[i][j] = a[i][j] - b[i][j];
	 return result;
}

Matrix3 operator * (const Matrix3& a, const Matrix3& b)
{
#define ROWCOL(i, j) \
    (a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j])
    return Matrix3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2),
                    ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2),
                    ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2));
#undef ROWCOL // (i, j)
}

Matrix3 operator * (const Matrix3& a, double d)
{ 
	 Matrix3 result;
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  result[i][j] = d * a[i][j];
	 return result;
}

Matrix3 operator * (double d, const Matrix3& a)
{ 
    return a*d; 
}

Matrix3 operator / (const Matrix3& a, double d)
{ 
	 Matrix3 result;
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  result[i][j] = a[i][j] / d;
	 return result;
}

int operator == (const Matrix3& a, const Matrix3& b)
{ 
	 double eps = 0.001; // very lenient tolerance
	 for (size_t i = 0; i < 3; i++)
	 	 for (size_t j = 0; j < 3; j++)
	 	 	  if (abs(a[i][j] - b[i][j]) > eps)
				   return 0;
	 return 1;
}

int operator != (const Matrix3& a, const Matrix3& b)
{ 
    return !(a == b); 
}

std::istream& operator >> (std::istream& s, Matrix3& v)
{
    double value;
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 3; j++)
        {
            s >> value;
            v[i][j] = value;
        }
    return s;
}

std::ostream& operator << (std::ostream& s, const Matrix3& v)
{
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 2; j++)
        {
            s << (float) v[i][j] << " ";
        }
        s << (float) v[i][2] << std::endl;
    }
    return s;
}


Vector3 operator * (const Matrix3& a, const Vector3& v)
{
#define ROWCOL(i) \
    (a[i][0]*v[0] + a[i][1]*v[1] + a[i][2]*v[2])
    return Vector3(ROWCOL(0), ROWCOL(1), ROWCOL(2));
#undef ROWCOL // (i)
}

void Matrix3::writeToGLMatrix(float* m) const
{
    m[0] = mM[0][0]; m[4] = mM[0][1]; m[8] = mM[0][2];  m[12] = 0.0f;
    m[1] = mM[1][0]; m[5] = mM[1][1]; m[9] = mM[1][2];  m[13] = 0.0f;
    m[2] = mM[2][0]; m[6] = mM[2][1]; m[10] = mM[2][2]; m[14] = 0.0f;
    m[3] = 0.0f;    m[7] = 0.0f;    m[11] = 0.0f;    m[15] = 1.0f;
}

glm::mat4 Matrix3::writeToMat4() const
{
    glm::mat4 m(1);
    for (int i = 0; i < 3; i++) {
       for (int j = 0; j < 3; j++) {
          m[i][j] = (float) mM[j][i];
       }
    }
    return m;
}

}
