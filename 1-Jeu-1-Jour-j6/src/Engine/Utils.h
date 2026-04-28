#pragma once

#include "Vector2f.h"
namespace Utils
{
	bool Normalize(Vector2f& vector);
	float GetDistance(int x1, int y1, int x2, int y2);
	float GetAngleDegree(const Vector2f& v1, const Vector2f& v2);
}