#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	// TODO
	return Quaternion(1,0,0,0);
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	// TODO
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	// TODO
}

Matrix3 Quaternion::toMatrix () const
{
	// TODO
	return Matrix3::Identity;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	// TODO
}

}