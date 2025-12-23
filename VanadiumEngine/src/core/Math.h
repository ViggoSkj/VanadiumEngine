#pragma once
#include "core/CoreTypes.h"

namespace Math
{
#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

	inline const float PI = E_PI;

	float Angle(Vector2 point);

	Vector2 RotatePoint(Vector2 point, Vector2 center, float rads);
	inline Vector2 RotatePoint(Vector2 point, float rads)
	{
		return RotatePoint(point, Vector2(0.0f, 0.0f), rads);
	}

	inline float Random()
	{
		return abs(rand() / (float)INT_MAX);
	}
}