#include "Vector3.h"

#include <cassert>
#include <cmath>

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::magnitude()
{
	float result = (x * x) + (y * y) + (z * z);
	return sqrtf(result);
}

float Vector3::magnitudeSqr()
{
	float result = (x * x) + (y * y) + (z * z);
	return result;
}

void Vector3::normalise()
{
	float mag = magnitude();

	_STL_ASSERT(mag != 0.0f, "Normalise: Divide by zero");
	assert(mag != 0.0f && "Normalise: Divide by zero");
	if (mag != 0.0f)
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

Vector3 Vector3::normaliseOther(const Vector3& other)
{
	Vector3 result(other.x, other.y, other.z);
	result.normalise();
	return result;
}

float Vector3::dot(const Vector3& rhs)
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

Vector3 Vector3::cross(Vector3 rhs)
{
	Vector3 result;
	result.x = (y * rhs.z) - (z * rhs.y);
	result.y = (z * rhs.x) - (x * rhs.z);
	result.z = (x * rhs.y) - (y * rhs.x);

	return result;
}

Vector3 Vector3::operator+(const Vector3& rhs)
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector3 Vector3::operator-(const Vector3& rhs)
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator*(float rhs)
{
	return Vector3(x * rhs, y * rhs, z * rhs);
}

Vector3 operator*(float lhs, Vector3 rhs)
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

Vector3 Vector3::operator/(float rhs)
{
	return Vector3(x / rhs, y / rhs, z / rhs);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3 Vector3::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vector3 Vector3::operator/=(float rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

float& Vector3::operator[](int index)
{
	//Easiest Format
	//if (index == 0)
	//	return x;
	//else if (index == 1)
	//	return y;

	//Richard Format
	//return *(&x + index);

	//Chris Format
	return ((float*)this)[index];
}

Vector3::operator float*()
{
	//return (float*)this;

	return &x;
}