#pragma once
#include <cmath>

class Vector2
{
public:
	float x{ 0 };
	float y{ 0 };

	//contrustors
	Vector2() = default;
	Vector2(float newX, float newY) : x(newX), y(newY) {}

	//+ operator. Return the result of adding the rhs to this
	Vector2 operator + (const Vector2& rhs) const {
		return Vector2(x + rhs.x, y + rhs.y);
	}

	//to do
	// - operator - returns the rsult of subtracting the rhs from this
	Vector2 operator - (const Vector2& rhs) const {
		return Vector2(x - rhs.x, y - rhs.y);
}
	// vector 2 operatior - (const Vectotor2 & RHS) CONST
	Vector2 operator * (float rhs) const {
		return Vector2(x * rhs, y* rhs);
	}

	// * OPERATOR MORE DETAILS ON WORLD CREATION VIDEO 12 46
	//ETC

	float Lenth() const {
		return sqrt(x * x + y * y);
	}

	void NormaliseInPlace() {
		float len = Lenth();

		if (len == 0)
			return;

			x /= len;
			y /= len;
	}

	float Dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}

	float Cross(const Vector2& other) const {
		return x * other.y - y * other.x;
	}
};

