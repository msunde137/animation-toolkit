#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
#include <cmath>

#define MOE .001
#define NEAR_0(x) ( x < MOE && x > -MOE )

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
	double y;
	double x;
	double z;

	if (NEAR_0(this->m13 - 1))
	{
		x = std::acos(this->m22);
		y = std::_Pi / 2.0;
		z = 0;
	}
	else if (NEAR_0(this->m13 + 1))
	{
		x = -std::acos(this->m22);
		y = -std::_Pi / 2.0;
		z = 0;
	}
	else
	{
		y = std::asin(this->m13);
		x = std::asin(this->m23 / -std::cos(y));
		z = std::asin(this->m12 / -std::cos(y));
	}

	return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
	double y;
	double x;
	double z;

	if (NEAR_0(this->m12 - 1))
	{
		x = std::acos(this->m33);
		y = 0;
		z = -std::_Pi / 2.0;
	}
	else if (NEAR_0(this->m12 + 1))
	{
		x = std::acos(this->m33);
		y = 0;
		z = std::_Pi / 2.0;
	}
	else
	{
		z = -std::asin(this->m12);
		x = std::acos(this->m22 / std::cos(z));
		y = -std::acos(this->m11 / std::cos(z));
	}

	return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
	double y;
	double x;
	double z;

	if (NEAR_0(this->m23 - 1))
	{
		z = -std::acos(this->m11);
		y = 0;
		x = -std::_Pi / 2.0;
	}
	else if (NEAR_0(this->m23 + 1))
	{
		z = std::acos(this->m11);
		y = 0;
		x = std::_Pi / 2.0;
	}
	else
	{
		x = -std::asin(this->m23);
		z = std::acos(this->m22 / std::cos(x));
		y = -std::acos(this->m33 / std::cos(x));
	}

	return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
	double y;
	double x;
	double z;

	if (NEAR_0(this->m21 - 1))
	{
		x = std::acos(this->m33);
		y = 0;
		z = std::_Pi / 2.0;
	}
	else if (NEAR_0(this->m21 + 1))
	{
		x = std::acos(this->m33);
		y = 0;
		z = -std::_Pi / 2.0;
	}
	else
	{
		z = std::asin(this->m21);
		x = std::acos(this->m22 / std::cos(z));
		y = -std::acos(this->m11 / std::cos(z));
	}

	return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
	double y;
	double x;
	double z;

	if (NEAR_0(this->m32 - 1))
	{
		z = -std::acos(this->m23);
		y = 0;
		x = std::_Pi / 2.0;
	}
	else if (NEAR_0(this->m32 + 1))
	{
		z = std::acos(this->m23);
		y = 0;
		x = -std::_Pi / 2.0;	
	}
	else
	{
		x = std::asin(this->m32);
		z = std::acos(this->m22 / std::cos(x));
		y = -std::acos(this->m33 / std::cos(x));
	}

	return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
	double y;
	double x;
	double z;

	if (NEAR_0(this->m31 - 1))
	{
		z = std::acos(this->m22);
		x = 0;
		y = -std::_Pi / 2.0;
	}
	else if (NEAR_0(this->m31 + 1))
	{
		z = std::acos(this->m22);
		x = 0;
		y = std::_Pi / 2.0;
	}
	else
	{
		y = -std::asin(this->m31);
		z = std::acos(this->m11 / std::cos(y));
		x = std::acos(this->m33 / std::cos(y));
	}

	return Vector3(x, y, z);
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
	double x = angleRad.x();
	double y = angleRad.y();
	double z = angleRad.z();

	*this = Matrix3(
		std::cos(y) * std::cos(z), -(std::cos(y) * std::sin(z)), std::sin(y),
		std::cos(z) * std::sin(x) * std::sin(y) + std::cos(x) * std::sin(z), std::cos(x) * std::cos(z) - std::sin(x) * std::sin(y) * std::sin(z), -(std::cos(y) * std::sin(x)),
		-(std::cos(x) * std::cos(z) * std::sin(y)) + std::sin(x) * std::sin(z), std::cos(z) * std::sin(x) + std::cos(x) * std::sin(y) * std::sin(z), std::cos(x) * std::cos(y)
	);
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
	double x = angleRad.x();
	double y = angleRad.y();
	double z = angleRad.z();

	*this = Matrix3(
		std::cos(y) * std::cos(z), -std::sin(z), std::cos(z) * std::sin(y),
		std::sin(x) * std::sin(y) + std::cos(x) * std::cos(y) * std::sin(z), std::cos(x) * std::cos(z), -(std::cos(y) * std::sin(x)) + std::cos(x) * std::sin(y) * std::sin(z),
		-(std::cos(x) * std::sin(y)) + std::cos(y) * std::sin(x) * std::sin(z), std::cos(z) * std::sin(x), std::cos(x) * std::cos(y) + std::sin(x) * std::sin(y) * std::sin(z)
	);
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
	double x = angleRad.x();
	double y = angleRad.y();
	double z = angleRad.z();

	*this = Matrix3(
		std::cos(y) * std::cos(z) + std::sin(x) * std::sin(y) * std::sin(z), std::cos(z) * std::sin(x) * std::sin(y) - std::cos(y) * std::sin(z), std::cos(x) * std::sin(y),
		std::cos(x) * std::sin(z), std::cos(x) * std::cos(z), -std::sin(x),
		-(std::cos(z) * std::sin(y)) + std::cos(y) * std::sin(x) * std::sin(z), std::cos(y) * std::cos(z) * std::sin(x) + std::sin(y) * std::sin(z), std::cos(x) * std::cos(y)
	);
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
	double x = angleRad.x();
	double y = angleRad.y();
	double z = angleRad.z();

	*this = Matrix3(
		std::cos(y) * std::cos(z), std::sin(x) * std::sin(y) - std::cos(x) * std::cos(y) * std::sin(z), std::cos(x) * std::sin(y) + std::cos(y) * std::sin(x) * std::sin(z),
		std::sin(z), std::cos(x) * std::cos(z), -(std::cos(z) * std::sin(x)),
		-(std::cos(z) * std::sin(y)), std::cos(y) * std::sin(x) + std::cos(x) * std::sin(y) * std::sin(z), std::cos(x) * std::cos(y) - std::sin(x) * std::sin(y) * std::sin(z)
	);
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
	double x = angleRad.x();
	double y = angleRad.y();
	double z = angleRad.z();

	*this = Matrix3(
		std::cos(y) * std::cos(z) - std::sin(x) * std::sin(y) * std::sin(z), -(std::cos(x) * std::sin(z)), std::cos(z) * std::sin(y) + std::cos(y) * std::sin(x) * std::sin(z),
		std::cos(z) * std::sin(x) * std::sin(y) + std::cos(y) * std::sin(z), std::cos(x) * std::cos(z), -(std::cos(y) * std::cos(z) * std::sin(x)) + std::sin(y) * std::sin(z),
		-(std::cos(x) * std::sin(y)), std::sin(x), std::cos(x) * std::cos(y)
	);
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
	double x = angleRad.x();
	double y = angleRad.y();
	double z = angleRad.z();

	*this = Matrix3(
		std::cos(y) * std::cos(z), std::cos(z) * std::sin(x) * std::sin(y) - std::cos(x) * std::sin(z), std::cos(x) * std::cos(z) * std::sin(y) + std::sin(x) * std::sin(z),
		std::cos(y) * std::sin(z), std::cos(x) * std::cos(z) + std::sin(x) * std::sin(y) * std::sin(z), -(std::cos(z) * std::sin(x)) + std::cos(x) * std::sin(y) * std::sin(z),
		-std::sin(y), std::cos(y) * std::sin(x), std::cos(x) * std::cos(y)
	);
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
	angleRad = std::acos((*this[0][0] + *this[1][1] + *this[2][2] - 1.0) / 2.0);
	axis[0] = (*this[2][1] - *this[1][2]) / std::sqrt((*this[2][1] - *this[1][2]) * 2.0 + (*this[0][2] - *this[2][0]) * 2.0 + (*this[1][0] - *this[0][1]) * 2.0);
	axis[1] = (*this[0][2] - *this[2][0]) / std::sqrt((*this[2][1] - *this[1][2]) * 2.0 + (*this[0][2] - *this[2][0]) * 2.0 + (*this[1][0] - *this[0][1]) * 2.0);
	axis[2] = (*this[1][0] - *this[0][1]) / std::sqrt((*this[2][1] - *this[1][2]) * 2.0 + (*this[0][2] - *this[2][0]) * 2.0 + (*this[1][0] - *this[0][1]) * 2.0);
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
	Matrix3 m1 = Matrix3::Identity;
	Matrix3 m2 = Matrix3(
		std::pow(axis[0], 2), axis[0] * axis[1], axis[0] * axis[2],
		axis[0] * axis[1], std::pow(axis[1], 2), axis[1] * axis[2],
		axis[0] * axis[2], axis[1] * axis[2], std::pow(axis[1], 2)
	);
	Matrix3 m3 = Matrix3(
		0, -axis[2], axis[1],
		axis[2], 0, -axis[0],
		-axis[1], axis[0], 0
	);

	*this = std::cos(angleRad)* m1 + (1 - std::cos(angleRad)) * m2 + std::sin(angleRad) * m3;
}

}