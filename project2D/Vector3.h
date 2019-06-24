#pragma once
struct Vector3
{
	Vector3();
	Vector3(float x, float y, float z);

	float magnitude();
	float magnitudeSqr();
	void normalise();
	static Vector3 normaliseOther(const Vector3& other);

	float dot(const Vector3& rhs);
	Vector3 cross(Vector3 rhs);

	Vector3 operator+(const Vector3& rhs);
	Vector3 operator-(const Vector3& rhs);
	Vector3 operator*(float rhs);
	Vector3 operator/(float rhs);
		  
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3 operator*=(float rhs);
	Vector3 operator/=(float rhs);

	float& operator[](int index);
	operator float*();

	float x;
	float y;
	float z;

};

Vector3 operator*(float lhs, Vector3 rhs);
