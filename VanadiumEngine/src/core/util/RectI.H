#pragma once
#include "core/CoreTypes.h"

struct RectI
{
	RectI(Vector2I start, Vector2I end)
		: start(start), end(end)
	{

	}

	bool Inside(Vector2 point);

	Vector2I start;
	Vector2I end;
};