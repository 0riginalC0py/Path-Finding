#include "Vector2.h"

#include <cmath>
#include <cassert>


Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2::magnitude()
{
	float result = (x * x) + (y * y);
	return sqrtf(result);
}

float Vector2::magnitudeSqr()
{
	float result = (x * x) + (y * y);
	return result;
}

void Vector2::normalise()
{
	float mag = magnitude();

	_STL_ASSERT(mag != 0.0f, "Normalise: Divide by zero");
	assert(mag != 0.0f && "Normalise: Divide by zero");
	if (mag != 0.0f)
	{
		x /= mag;
		y /= mag;
	}
}

Vector2 Vector2::normaliseOther(const Vector2& other)
{
	Vector2 result(other.x, other.y);
	result.normalise();
	return result;
}

float Vector2::dot(const Vector2& rhs)
{
	return (x * rhs.x) + (y * rhs.y);
}

Vector2 Vector2::right()
{
	return Vector2(-y, x);
}

Vector2 Vector2::operator+(const Vector2& rhs)
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(float rhs)
{
	return Vector2(x * rhs, y * rhs);
}

Vector2 operator*(float lhs, Vector2 rhs)
{
	return Vector2(lhs * rhs.x, lhs * rhs.y);
}

Vector2 Vector2::operator/(float rhs)
{
	return Vector2(x / rhs, y / rhs);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2 Vector2::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vector2 Vector2::operator/=(float rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

float& Vector2::operator[](int index)
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

Vector2::operator float*()
{
	//return (float*)this;

	return &x;
}