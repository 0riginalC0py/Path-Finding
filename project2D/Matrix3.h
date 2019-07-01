#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Math.h"

class Matrix3
{
public:
	Matrix3();
	Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);
	~Matrix3();

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);
	void RotateX(float radians);
	void RotateY(float radians);
	void RotateZ(float radians);

	void setPosition(float x, float y);
	void setPosition(Vector2 pos);
	void Translate(float x, float y);
	void Translate(Vector2 v2);


	void setScale(float x, float y);
	void setScale(Vector2 pos);
	void Scale(float width, float height);
	void Scale(Vector2 v2);

	Vector2 getPostion();
	float getRotation();
	Vector2 getScale();

	Matrix3 operator*(const Matrix3& rhs);
	Vector3 operator*(const Vector3& rhs);
	Vector3& operator[](int index);
	operator float*();

	/* Matrix
	0, 3, 6
	1, 4, 7
	2, 5, 8
	*/
	float m[9];
};

