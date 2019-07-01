#include "Matrix3.h"

//-----------------------------------------------
//Constructors
//-----------------------------------------------

Matrix3::Matrix3()
{
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 1;
	m[5] = 0;
	m[6] = 0;
	m[7] = 0;
	m[8] = 1;
}

Matrix3::Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8)
{
	m[0] = m0;
	m[1] = m1;
	m[2] = m2;
	m[3] = m3;
	m[4] = m4;
	m[5] = m5;
	m[6] = m6;
	m[7] = m7;
	m[8] = m8;
}


Matrix3::~Matrix3()
{
}

//-----------------------------------------------
//Functions
//-----------------------------------------------

void Matrix3::setRotateX(float radians)
{
	m[4] = cosf(radians);
	m[5] = sinf(radians);

	m[7] = -sinf(radians);
	m[8] = cosf(radians);
}

void Matrix3::RotateX(float radians)
{
	Matrix3 m;
	m.setRotateX(radians);
	*this = *this * m;
}

void Matrix3::setRotateY(float radians)
{
	m[0] = cosf(radians);
	m[2] = -sinf(radians);

	m[6] = sinf(radians);
	m[8] = cosf(radians);
}

void Matrix3::RotateY(float radians)
{
	Matrix3 m;
	m.setRotateY(radians);
	*this = *this * m;
}

void Matrix3::setRotateZ(float radians)
{
	m[0] = cosf(radians);
	m[1] = sinf(radians);

	m[3] = -sinf(radians);
	m[4] = cosf(radians);
}

void Matrix3::RotateZ(float radians)
{
	Matrix3 m;
	m.setRotateZ(radians);
	*this = *this * m;
}

void Matrix3::setPosition(float x, float y)
{
	m[6] = x;
	m[7] = y;
}

void Matrix3::setPosition(Vector2 pos)
{
	setPosition(pos.m_x, pos.m_y);
}

void Matrix3::Translate(float x, float y)
{
	Matrix3 m;
	m.setPosition(x, y);
	*this = m * *this;
}
//Does not work. Needs to be vector 3.
void Matrix3::Translate(Vector2 v2)
{
	Matrix3 m;
	m.setPosition(v2.m_x, v2.m_y);
	*this = *this * m;
}

void Matrix3::setScale(float width, float height)
{
	m[0] = width;
	m[1] = 0;
	m[3] = 0;
	m[4] = height;
}

void Matrix3::setScale(Vector2 pos)
{
	setScale(pos.m_x, pos.m_y);
}

void Matrix3::Scale(float width, float height)
{
	Matrix3 m;
	m.setPosition(width, height);
	*this = *this * m;
}

void Matrix3::Scale(Vector2 v2)
{
	Matrix3 m;
	m.setPosition(v2.m_x, v2.m_y);
	*this = *this * m;
}

//-----------------------------------------------
//Getters
//-----------------------------------------------

Vector2 Matrix3::getPostion()
{

	return Vector2(m[6], m[7]);
}
//NOT CORRECT FIX
float Matrix3::getRotation()
{
	return 5;
}

Vector2 Matrix3::getScale()
{
	return Vector2(m[0], m[4]);
}

//-----------------------------------------------
//Operators
//-----------------------------------------------

Matrix3 Matrix3::operator*(const Matrix3& rhs)
{
	Matrix3 result;
	result.m[0] = m[0] * rhs.m[0] + m[3] * rhs.m[1] + m[6] * rhs.m[2];
	result.m[1] = m[1] * rhs.m[0] + m[4] * rhs.m[1] + m[7] * rhs.m[2];
	result.m[2] = m[2] * rhs.m[0] + m[5] * rhs.m[1] + m[8] * rhs.m[2];
	result.m[3] = m[0] * rhs.m[3] + m[3] * rhs.m[4] + m[6] * rhs.m[5];
	result.m[4] = m[1] * rhs.m[3] + m[4] * rhs.m[4] + m[7] * rhs.m[5];
	result.m[5] = m[2] * rhs.m[3] + m[5] * rhs.m[4] + m[8] * rhs.m[5];
	result.m[6] = m[0] * rhs.m[6] + m[3] * rhs.m[7] + m[6] * rhs.m[8];
	result.m[7] = m[1] * rhs.m[6] + m[4] * rhs.m[7] + m[7] * rhs.m[8];
	result.m[8] = m[2] * rhs.m[6] + m[5] * rhs.m[7] + m[8] * rhs.m[8];
	

	return result;
}

Vector3 Matrix3::operator*(const Vector3& rhs)
{
	Vector3 result;
	result.m_x = m[0] * rhs.m_x + m[3] * rhs.m_y + m[6] * rhs.m_z;
	result.m_y = m[1] * rhs.m_x + m[4] * rhs.m_y + m[7] * rhs.m_z;
	result.m_z = m[2] * rhs.m_x + m[5] * rhs.m_y + m[8] * rhs.m_z;


	return result;
}

Vector3& Matrix3::operator[](int index)
{
	return*((Vector3*)&m[index * 3]);
}

Matrix3::operator float*()
{
	return (float*)this;
}