#include "Vector4.h"
#include "math.h"


Vector4::Vector4()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_w = 0;
}


Vector4::Vector4(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}


Vector4::~Vector4()
{
}
//Gets the magnitude of a vector(float) squared
float Vector4::magnitude()
{
	float result = (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
	return sqrtf(result);
}
//Gets the magnitude of a vector(float) unsquared
float Vector4::magnitudeSqr()
{
	float result = (m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w);
	return result;
}
//(float)
float Vector4::dot(const Vector4& rhs)
{
	return (m_x * rhs.m_x) + (m_y * rhs.m_y) + (m_z * rhs.m_z) + (m_w * rhs.m_w);
}

//Returns the cross product as a vector.
Vector4 Vector4::cross(const Vector4& right)
{
	Vector4 result;
	result.m_x = (m_y * right.m_z) - (m_z * right.m_y);
	result.m_y = (m_z * right.m_x) - (m_x * right.m_z);
	result.m_z = (m_x * right.m_y) - (m_y * right.m_x);
	result.m_w = 0;
	return result;
}
//Normalises a vector
void Vector4::normalise()
{
	float mag = magnitude();
	if (mag != 0.0f)
	{
		m_x /= mag;
		m_y /= mag;
		m_z /= mag;
		m_w /= mag;
	}
}

Vector4 Vector4::normaliseOther(Vector4 other)
{
	Vector4 result(other.m_x, other.m_y, other.m_y, other.m_w);
	result.normalise();
	return result;
}

//-----------------------------------------------
//Operators
//-----------------------------------------------

//Adds 2 vectors and returns a vector as a result
Vector4 Vector4::operator +(const Vector4& right)
{
	Vector4 result;
	result.m_x = m_x + right.m_x;
	result.m_y = m_y + right.m_y;
	result.m_z = m_z + right.m_z;
	result.m_w = m_w + right.m_w;
	return result;
}
//Subtracts 2 vectors and returns a vector as a result
Vector4 Vector4::operator -(const Vector4& right)
{
	Vector4 result;
	result.m_x = m_x - right.m_x;
	result.m_y = m_y - right.m_y;
	result.m_z = m_z - right.m_z;
	result.m_w = m_w - right.m_w;
	return result;
}
//Times vector by float(Vector)
Vector4 Vector4::operator *(float right)
{
	Vector4 result;
	result.m_x = m_x * right;
	result.m_y = m_y * right;
	result.m_z = m_z * right;
	result.m_w = m_w * right;
	return result;
}

Vector4 operator*(float left, Vector4 right)
{
	Vector4 result;
	result.m_x = left * right.m_x;
	result.m_y = left * right.m_y;
	result.m_z = left * right.m_z;
	result.m_w = left * right.m_w;
	return result;
}

Vector4 Vector4::operator/ (float right)
{
	Vector4 result;
	result.m_x = m_x / right;
	result.m_y = m_y / right;
	result.m_z = m_z / right;
	result.m_w = m_w / right;
	return result;
}

void Vector4::operator+=(const Vector4& rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	m_z += rhs.m_z;
	m_w += rhs.m_w;
}

void Vector4::operator-=(const Vector4& rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	m_z -= rhs.m_z;
	m_w -= rhs.m_w;
}

float& Vector4::operator[](int iterator)
{
	return *(&m_x + iterator);
}

Vector4::operator float*()
{
	return &m_x;
}