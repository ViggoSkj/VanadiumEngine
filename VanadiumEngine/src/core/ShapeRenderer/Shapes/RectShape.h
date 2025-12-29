#pragma once
#include "core/CoreTypes.h"

namespace Vanadium
{
	struct RectShape
	{
		RectShape(Vector2 center, Vector2 size, float rotation)
			: Center(center), Size(size), Rotation(rotation)
		{

		}

		Vector2 Center;
		Vector2 Size;
		float Rotation;
	};
}