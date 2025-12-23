#pragma once
#include "core/CoreTypes.h"

struct CircleShape
{
	CircleShape(Vector2 center, float radius)
		: Center(center), Radius(radius)
	{

	}
	Vector2 Center;
	float Radius;
};