#pragma once
class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	float magnitude();
	float magnitudeSqr();
	void normalise();
	Vector3 normaliseOther(Vector3 other);
	Vector3 cross(const Vector3& right);
	float dot(const Vector3& rhs);

	float m_x, m_y, m_z;

	Vector3 operator +(const Vector3& right);
	Vector3 operator -(const Vector3& right);
	Vector3 operator *(float right);
	Vector3 operator /(float right);
	void operator +=(const Vector3& right);
	void operator -=(const Vector3& right);
	float& operator[](int iterator);
	operator float*();
};

Vector3 operator*(float left, Vector3 right);