#include "Vector3.h"
#include "math.h"


Vector3::Vector3()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}


Vector3::~Vector3()
{
}
//Gets the magnitude of a vector(float) squared
float Vector3::magnitude()
{
	float result = (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
	return sqrtf(result);
}
//Gets the magnitude of a vector(float) unsquared
float Vector3::magnitudeSqr()
{
	float result = (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
	return result;
}
//(float)
float Vector3::dot(const Vector3& rhs)
{
	return (m_x * rhs.m_x) + (m_y * rhs.m_y) + (m_z * rhs.m_z);
}

//Returns the cross product as a vector.
Vector3 Vector3::cross(const Vector3& right)
{
	Vector3 result;
	result.m_x = (m_y * right.m_z) - (m_z * right.m_y);
	result.m_y = (m_z * right.m_x) - (m_x * right.m_z);
	result.m_z = (m_x * right.m_y) - (m_y * right.m_x);
	return result;
}
//Normalises a vector
void Vector3::normalise()
{
	float mag = magnitude();
	if (mag != 0.0f)
	{
		m_x /= mag;
		m_y /= mag;
		m_z /= mag;
	}
}

Vector3 Vector3::normaliseOther(Vector3 other)
{
	Vector3 result(other.m_x, other.m_y, other.m_y);
	result.normalise();
	return result;
}

//-----------------------------------------------
//Operators
//-----------------------------------------------

//Adds 2 vectors and returns a vector as a result
Vector3 Vector3::operator +(const Vector3& right)
{
	Vector3 result;
	result.m_x = m_x + right.m_x;
	result.m_y = m_y + right.m_y;
	result.m_z = m_z + right.m_z;
	return result;
}
//Subtracts 2 vectors and returns a vector as a result
Vector3 Vector3::operator -(const Vector3& right)
{
	Vector3 result;
	result.m_x = m_x - right.m_x;
	result.m_y = m_y - right.m_y;
	result.m_z = m_z - right.m_z;
	return result;
}
//Times vector by float(Vector)
Vector3 Vector3::operator *(float right)
{
	Vector3 result;
	result.m_x = m_x * right;
	result.m_y = m_y * right;
	result.m_z = m_z * right;
	return result;
}

Vector3 operator*(float left, Vector3 right)
{
	Vector3 result;
	result.m_x = left * right.m_x;
	result.m_y = left * right.m_y;
	result.m_z = left * right.m_z;
	return result;
}


Vector3 Vector3::operator/(float right)
{
	Vector3 result;
	result.m_x = m_x / right;
	result.m_y = m_y / right;
	result.m_z = m_z / right;
	return result;
}



void Vector3::operator+=(const Vector3& rhs)
{
	m_x += rhs.m_x;
	m_x += rhs.m_y;
	m_z += rhs.m_z;
}

void Vector3::operator-=(const Vector3& rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	m_z -= rhs.m_z;
}

float& Vector3::operator[](int iterator)
{
	return *(&m_x + iterator);
}

Vector3::operator float*()
{
	return &m_x;
}