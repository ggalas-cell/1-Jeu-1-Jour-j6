#include "Vector2f.h"
#include <iostream>

Vector2f::Vector2f(float _x, float _y) {
    x = _x;
    y = _y;
}

Vector2f::Vector2f()
{
    x = 0;
    y = 0;
}

float Vector2f::GetX()
{
    return x;
}

float Vector2f::GetY()
{
    return y;
}

void Vector2f::SetX(float _newX)
{
    x = _newX;
}

void Vector2f::SetY(float _newY)
{
    y = _newY;
}

void Vector2f::SetValue(float _x, float _y)
{
    x = _x;
    y = _y;
}

Vector2f Vector2f::Normalize()
{
    float d = Length();

    if (d == 0)
    {
        return Vector2f(0, 0);
    }

    float x = GetX() / d;
    float y = GetY() / d;

    return Vector2f(x, y);
}

float Vector2f::Length() const
{
    return std::sqrt(x * x + y * y);
}

float Vector2f::Dot(const Vector2f& other) const
{
    return x * other.x + y * other.y;
}

Vector2f Vector2f::operator+(const Vector2f& right)
{
    return Vector2f(x + right.x, y + right.y);
}

Vector2f Vector2f::operator-(const Vector2f& right)
{
    return Vector2f(x - right.x, y - right.y);
}

Vector2f Vector2f::operator*(float right)
{
    return Vector2f(x * right, y * right);
}

Vector2f Vector2f::operator/(float right)
{
    return Vector2f(x / right, y / right);
}