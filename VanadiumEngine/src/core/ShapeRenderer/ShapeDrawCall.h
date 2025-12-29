#pragma once
#include "core/CoreTypes.h"

namespace Vanadium
{
	struct ShapeDrawCall
	{
		ShapeDrawCall(u8 shapeBuffer, Vector4 color)
			: ShapeBuffer(shapeBuffer), Color(color)
		{

		}

		u8 ShapeBuffer;
		Vector4 Color;
	};
}