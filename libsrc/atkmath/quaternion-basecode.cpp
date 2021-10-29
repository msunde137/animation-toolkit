#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	//
	// my original function was deleted, so I'm using the code on
	// https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
	// (it does basically the same thing)
	//

	// quaternion to return
	Quaternion qm;
	// Calculate angle between them.
	double cosHalfTheta = q0.mW * q1.mW + q0.mX * q1.mX + q0.mY * q1.mY + q0.mZ * q1.mZ;
	// if q0=q1 or q0=-q1 then theta = 0 and we can return q0
	if (abs(cosHalfTheta) >= 1.0) {
		qm.mW = q0.mW; qm.mX = q0.mX; qm.mY = q0.mY; qm.mZ = q0.mZ;
		return qm;
	}
	// Calculate temporary values.
	double halfTheta = acos(cosHalfTheta);
	double sinHalfTheta = sqrt(1.0 - cosHalfTheta * cosHalfTheta);
	// if theta = 180 degrees then result is not fully defined
	// we could rotate around any axis normal to q0 or q1
	if (fabs(sinHalfTheta) < 0.001) { // fabs is floating point absolute
		qm.mW = (q0.mW * 0.5 + q1.mW * 0.5);
		qm.mX = (q0.mX * 0.5 + q1.mX * 0.5);
		qm.mY = (q0.mY * 0.5 + q1.mY * 0.5);
		qm.mZ = (q0.mZ * 0.5 + q1.mZ * 0.5);
		return qm;
	}
	double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
	double ratioB = sin(t * halfTheta) / sinHalfTheta;
	//calculate Quaternion.
	qm.mW = (q0.mW * ratioA + q1.mW * ratioB);
	qm.mX = (q0.mX * ratioA + q1.mX * ratioB);
	qm.mY = (q0.mY * ratioA + q1.mY * ratioB);
	qm.mZ = (q0.mZ * ratioA + q1.mZ * ratioB);
	return qm;
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	angleRad = 2.0 * std::acos(mW);
	double x = mX / sqrt(1 - mW * mW);
	double y = mY / sqrt(1 - mW * mW);
	double z = mZ / sqrt(1 - mW * mW);
	axis = Vector3(x, y, z);
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	mX = axis.x() * sin(angleRad / 2);
	mY = axis.y() * sin(angleRad / 2);
	mZ = axis.z() * sin(angleRad / 2);
	mW = std::cos(angleRad / 2);
}

Matrix3 Quaternion::toMatrix () const
{
	return Matrix3(
		1 - 2 * mY * mY - 2 * mZ * mZ, 2 * mZ * mY - 2 * mZ * mW, 2 * mX * mZ + 2 * mY * mW,
		2 * mX * mY + 2 * mZ * mW, 1 - 2 * mX * mX - 2 * mZ * mZ, 2 * mY * mZ - 2 * mX * mW,
		2 * mX * mZ - 2 * mY * mW, 2 * mY * mZ + 2 * mX * mW, 1 - 2 * mX * mX - 2 * mY * mY
	);
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	mW = std::sqrt(1 + rot[0][0] + rot[1][1] + rot[2][2]) / 4.0;
	mX = (rot[2][1] - rot[1][2]) / (4.0 * mW);
	mY = (rot[0][2] - rot[2][0]) / (4.0 * mW);
	mZ = (rot[1][0] - rot[0][1]) / (4.0 * mW);
}

}