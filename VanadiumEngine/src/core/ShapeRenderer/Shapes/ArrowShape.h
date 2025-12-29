#pragma once
#include "core/CoreTypes.h"

namespace Vanadium
{
	struct ArrowShape
	{
		ArrowShape(Vector2 start, Vector2 end)
			: Start(start), End(end)
		{

		}

		Vector2 Start;
		Vector2 End;
	};
}