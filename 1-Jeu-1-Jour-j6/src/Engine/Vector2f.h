#pragma once
#include <SFML/Graphics.hpp>

class Vector2f : public sf::Vector2f {
public:
	Vector2f(float _x, float _y);
	Vector2f();
	float GetX();
	float GetY();
	void SetX(float _newX);
	void SetY(float _newY);
	void SetValue(float _x, float _y);
	Vector2f Normalize();

	float Length() const;
	float Dot(const Vector2f& other) const;

	Vector2f operator+(const Vector2f& right);
	Vector2f operator-(const Vector2f& right);
	Vector2f operator*(float right);
	Vector2f operator/(float right);
};