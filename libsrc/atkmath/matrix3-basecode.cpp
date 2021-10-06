#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   return Vector3();
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   // TODO
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   // TODO
   *this = Identity;
}

}