#include "Vector4.h"

#include <cmath>
#include <cassert>


Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vector4::magnitude()
{
	float result = (x * x) + (y * y) + (z * z) + (w * w);
	return sqrtf(result);
}

float Vector4::magnitudeSqr()
{
	float result = (x * x) + (y * y) + (z * z) + (w * w);
	return result;
}

void Vector4::normalise()
{
	float mag = magnitude();

	_STL_ASSERT(mag != 0.0f, "Normalise: Divide by zero");
	assert(mag != 0.0f && "Normalise: Divide by zero");
	if (mag != 0.0f)
	{
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
}

Vector4 Vector4::normaliseOther(const Vector4& other)
{
	Vector4 result(other.x, other.y, other.z, other.w);
	result.normalise();
	return result;
}

float Vector4::dot(const Vector4& rhs)
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
}

Vector4 Vector4::cross(Vector4 rhs)
{
	Vector4 result;
	result.x = (y * rhs.z) - (z * rhs.y);
	result.y = (z * rhs.x) - (x * rhs.z);
	result.z = (x * rhs.y) - (y * rhs.x);
	result.w = 0;

	return result;
}

Vector4 Vector4::operator+(const Vector4& rhs)
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Vector4 Vector4::operator-(const Vector4& rhs)
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

Vector4 Vector4::operator*(float rhs)
{
	return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

Vector4 operator*(float lhs, Vector4 rhs)
{
	return Vector4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
}

Vector4 Vector4::operator/(float rhs)
{
	return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

Vector4& Vector4::operator+=(const Vector4& rhs)
{
	//Easy Way
	//x += rhs.x;
	//y += rhs.y;
	//z += rhs.z;
	//w += rhs.w;

	//Eric Way
	*this = *this + rhs;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

Vector4 Vector4::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}

Vector4 Vector4::operator/=(float rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;
	return *this;
}

float& Vector4::operator[](int index)
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

Vector4::operator float*()
{
	//return (float*)this;

	return &x;
}