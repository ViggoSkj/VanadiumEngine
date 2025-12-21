#pragma once
#include "core/CoreTypes.h"

namespace Math
{
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