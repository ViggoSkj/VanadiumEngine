#pragma once
#include "core/CoreTypes.h"

struct Rect
{
	Rect(Vector2 start = Vector2(0, 0), Vector2 end = Vector2(1, 1))
		: Start(start), End(end) {}

	Vector2 Start;
	Vector2 End = Vector2(1, 1);

	float Width() const { return End.x - Start.x; }
	float Height() const { return End.y - Start.y; }

	float Width2() const { return Width() * Width(); }
	float Height2() const { return Height() * Height(); }

	bool Overlaps(Rect other);
	bool Overlaps(Vector2 offset, Rect other, Vector2 offsetOther);
};