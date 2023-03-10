#include "VMEngine2D/Vector2.h"

using namespace std;


Vector2::Vector2(float x, float y)
{
	//this->x is the class variable
	//x is the paramater
	//all function will use the parameter name over the class name
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator+(const Vector2& OtherVector)
{
	//add current vectors x with the other vectors x
	//vector2(1, 2) + vector2(1, 1) = vector2(1, 3)
	return Vector2(this->x + OtherVector.x, this->y + OtherVector.y);
}

Vector2 Vector2::operator+=(const Vector2& OtherVector)
{
	//increment the x and y values of this vector by the other vector
	this->x += OtherVector.x;
	this->y += OtherVector.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& OtherVector)
{
	//minus current vectors x with the other vectors x
	//vector2(1, 2) - vector2(1, 1) = vector2(0, 1)
	return Vector2(this->x - OtherVector.x, this->y - OtherVector.y);
}

Vector2 Vector2::operator-=(const Vector2& OtherVector)
{
	//decrement the x and y values of this vector by the other vector
	this->x -= OtherVector.x;
	this->y -= OtherVector.y;

	return *this;
}

Vector2 Vector2::operator*(const float& Scalar)
{
	//Multiplying the x and y of this current vector by a float value
	//Vector2(1.0f,2.0f) * 5.0f = ector2(5.0f,10.0f)
	return Vector2(this->x * Scalar, this->y * Scalar);
}

Vector2 Vector2::operator*=(const float& Scalar)
{
	//Multiply the vector by itself and a scaler value
	this->x *= Scalar;
	this->y *= Scalar;
	return *this;
}

Vector2 Vector2::operator/(const float& Scalar)
{
	Vector2 DivivedVector = Vector2(0.0f, 0.0f);

	//Only do the division if we don't divide by 0.0f
	if (Scalar != 0.0f) {
		DivivedVector.x = this->x / Scalar;
		DivivedVector.y = this->y / Scalar;
	}
	else {
		//Warn the programmer they divided by 0.0f
		cout << "Cannot divide Vector2 by 0.0f" << endl;
	}
	return DivivedVector;
}

Vector2 Vector2::operator/=(const float& Scalar)
{
	//we're dividing the current vector by a float value
	//a = Vector2(2.0f, 5.0f) /= 2.0f
	//a = Vector2(1.0f, 2.5f)

	//Only do the division if we don't divide by 0.0f
	if (Scalar != 0.0f) {
		this->x / Scalar;
		this->y / Scalar;
	}
	else {
		//Warn the programmer they divided by 0.0f
		cout << "Cannot divide Vector2 by 0.0f" << endl;
	}
	return *this;
}

bool Vector2::operator==(const Vector2& OtherVector)
{
	//return true if the 2 vectors match
	bool bMatchX = this->x == OtherVector.x;
	bool bMatchY = this->y == OtherVector.y;

	//the boolean operator && will return false if one of them isn't true
	return bMatchX && bMatchY;
}

bool Vector2::operator!=(const Vector2& OtherVector)
{
	//return true if the 2 vectors don't match x or y
	bool bMatchX = this->x != OtherVector.x;
	bool bMatchY = this->y != OtherVector.y;

	//the boolean operator && will return false if one of them isn't true
	return bMatchX && bMatchY;
}

float Vector2::Length()
{
	//return the size of the vector using its x and y
	return sqrtf(x * x + y * y);
}

void Vector2::Normalise()
{
	//ithis will devide the vector by its length and will change the value
		*this /= max(Length(), 1.0f);
}

Vector2 Vector2::Normalised()
{
	//devine the vector by its length and return the value but not change the vector
	Vector2 Result = Vector2(0.0f, 0.0f);
	Result = *this / max(Length(), 1.0f);

	return Result;
}

Vector2 Vector2::Zero()
{
	//returning a complete 0.0f vector
	return Vector2(0, 0);
}
