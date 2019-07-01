#pragma once
class Vector4
{
public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	~Vector4();

	float magnitude();
	float magnitudeSqr();
	void normalise();
	Vector4 normaliseOther(Vector4 other);
	Vector4 cross(const Vector4& right);
	float dot(const Vector4& rhs);

	float m_x, m_y, m_z, m_w;

	Vector4 operator +(const Vector4& right);
	Vector4 operator -(const Vector4& right);
	Vector4 operator *(float right);
	Vector4 operator /(float right);
	void operator +=(const Vector4& right);
	void operator -=(const Vector4& right);
	float& operator[](int iterator);
	operator float*();
};

Vector4 operator*(float left, Vector4 right);