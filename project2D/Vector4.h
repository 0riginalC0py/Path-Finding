#pragma once
struct Vector4
{
	Vector4();
	Vector4(float x, float y, float z, float w);

	float magnitude();
	float magnitudeSqr();
	void normalise();
	static Vector4 normaliseOther(const Vector4& other);

	float dot(const Vector4& rhs);
	Vector4 cross(Vector4 rhs);

	Vector4 operator+(const Vector4& rhs);
	Vector4 operator-(const Vector4& rhs);
	Vector4 operator*(float rhs);
	Vector4 operator/(float rhs);

	Vector4& operator+=(const Vector4& rhs);
	Vector4& operator-=(const Vector4& rhs);
	Vector4 operator*=(float rhs);
	Vector4 operator/=(float rhs);

	float& operator[](int index);
	operator float*();

	float x;
	float y;
	float z;
	float w;

};

Vector4 operator*(float lhs, Vector4 rhs);