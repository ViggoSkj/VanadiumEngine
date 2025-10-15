#pragma once
#include "core/CoreTypes.h"

struct Rect
{
	Vector2 Start;
	Vector2 End = Vector2(2,2);

	bool Overlaps(Rect other);
	bool Overlaps(Vector2 offset, Rect other, Vector2 offsetOther);
};