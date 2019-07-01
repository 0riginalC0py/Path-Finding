#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	float magnitude();
	float magnitudeSqr();
	void normalise();
	Vector2 normaliseOther(Vector2 right);
	Vector2 right();
	float dot(const Vector2& rhs);

	float m_x, m_y;

	Vector2 operator +(const Vector2& right);
	Vector2 operator -(const Vector2& right);
	Vector2 operator *(float right);
	Vector2 operator /(float right);
	void operator +=(const Vector2& right);
	void operator -=(const Vector2& right);
	float& operator[](int iterator);
	operator float*();
};

Vector2 operator*(float left, Vector2 right);