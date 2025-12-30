#pragma once
#include "core/CoreTypes.h"

struct RectI
{
	RectI(Vector2I start, Vector2I end)
		: start(start), end(end)
	{

	}

	Vector2I start;
	Vector2I end;
};