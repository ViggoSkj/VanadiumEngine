#pragma once
#include "core/CoreTypes.h"

struct Rect
{
	Vector2 Start;
	Vector2 End = Vector2(2, 2);

	float Width() const { return End.x - Start.x; }
	float Height() const { return End.y - Start.y; }

	float Width2() const { return Width() * Width(); }
	float Height2() const { return Height() * Height(); }

	bool Overlaps(Rect other);
	bool Overlaps(Vector2 offset, Rect other, Vector2 offsetOther);
};