#include "Vector2.h"
#include "math.h"

Vector2::Vector2()
{
	m_x = 0;
	m_y = 0;
}


Vector2::Vector2(float x , float y)
{
	m_x = x;
	m_y = y;
}


Vector2::~Vector2()
{
}

//Gets the magnitude of a vector(float) squared
float Vector2::magnitude()
{
	float result = (m_x * m_x) + (m_y * m_y);
	return sqrtf(result);
}
//Gets the magnitude of a vector(float) unsquared
float Vector2::magnitudeSqr()
{
	float result = (m_x * m_x) + (m_y * m_y);
	return result;
}
//Normalises a vector
void Vector2::normalise()
{
	float mag = magnitude();
	if (mag != 0.0f)
	{
		m_x /= mag;
		m_y /= mag;
	}
}

Vector2 Vector2::normaliseOther(Vector2 other)
{
	Vector2 result(other.m_x, other.m_y);
	result.normalise();
	return result;
}
//(float)
float Vector2::dot(const Vector2& rhs)
{
	return (m_x * rhs.m_x) + (m_y * rhs.m_y);
}
//Returns a right angle triangle when compated against original vector(Vector).
Vector2 Vector2::right()
{
	return Vector2(-m_y, m_x);
}

//-----------------------------------------------
//Operators
//-----------------------------------------------

//Adds 2 vectors and returns a vector as a result
Vector2 Vector2::operator +(const Vector2& right)
{
	Vector2 result;
	result.m_x = m_x + right.m_x;
	result.m_y = m_y + right.m_y;
	return result;
}
//Subtracts 2 vectors and returns a vector as a result
Vector2 Vector2::operator -(const Vector2& right)
{
	Vector2 result;
	result.m_x = m_x - right.m_x;
	result.m_y = m_y - right.m_y;
	return result;
}
//Times vector by float(Vector)
Vector2 Vector2::operator* (float right)
{
	Vector2 result;
	result.m_x = m_x * right;
	result.m_y = m_y * right;
	return result;
}

Vector2 operator*(float left, Vector2 right)
{
	Vector2 result;
	result.m_x = left * right.m_x;
	result.m_y = left * right.m_y;
	return result;
}

Vector2 Vector2::operator/(float right)
{
	Vector2 result;
	result.m_x = m_x * right;
	result.m_y = m_y * right;
	return result;
}


void Vector2::operator+=(const Vector2& rhs)
{
	m_x += rhs.m_x;
	m_x += rhs.m_y;
}

void Vector2::operator-=(const Vector2& rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
}

float& Vector2::operator[](int iterator)
{
	return *(&m_x + iterator);
}

Vector2::operator float*()
{
	return &m_x;
}