#pragma once
struct Vector2
{
	Vector2();
	Vector2(float x, float y);

	float magnitude();
	float magnitudeSqr();
	void normalise();
	static Vector2 normaliseOther(const Vector2& other);

	float dot(const Vector2& rhs);
	Vector2 right();

	Vector2 operator+(const Vector2& rhs);
	Vector2 operator-(const Vector2& rhs);
	Vector2 operator*(float rhs);
	Vector2 operator/(float rhs);
	
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2 operator*=(float rhs);
	Vector2 operator/=(float rhs);

	float& operator[](int index);
	operator float*();

	float x;
	float y;
};

Vector2 operator*(float lhs, Vector2 rhs);