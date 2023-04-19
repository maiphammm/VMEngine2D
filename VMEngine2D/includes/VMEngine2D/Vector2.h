#pragma once
#include <iostream>

class Vector2 {
public:
	//initialise vectors to 0
	Vector2() { x = y = 0.0f; }
	Vector2(float x, float y);
	~Vector2() {};

	//Below are the math operators for our vector class
	//Addition operators
	Vector2 operator+(const Vector2& OtherVector);
	Vector2 operator+=(const Vector2& OtherVector);

	//Subtraction operators
	Vector2 operator-(const Vector2& OtherVector);
	Vector2 operator-=(const Vector2& OtherVector);

	//Multiplication operators
	Vector2 operator*(const float& Scalar);
	Vector2 operator*=(const float& Scalar);

	//Division operators
	Vector2 operator/(const float& Scalar);
	Vector2 operator/=(const float& Scalar);

	//Boolean operators
	bool operator==(const Vector2& OtherVector);
	bool operator!=(const Vector2& OtherVector);

	//Get the magnitude/length of the vector
	float Length();

	//normalise the vector
	void Normalise();
	Vector2 Normalised();

	//return a zero vector
	static Vector2 Zero();


public: 
	float x, y;
};