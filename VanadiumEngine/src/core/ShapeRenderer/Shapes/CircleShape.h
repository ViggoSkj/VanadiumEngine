#pragma once
#include "core/CoreTypes.h"

namespace Vanadium
{
	struct CircleShape
	{
		CircleShape(Vector2 center, float radius)
			: Center(center), Radius(radius)
		{

		}
		Vector2 Center;
		float Radius;
	};
}