#pragma once
#include "core/CoreTypes.h"

struct Rect
{
	Rect(Vector2 start = Vector2(0, 0), Vector2 end = Vector2(1, 1))
		: Start(start), End(end) {}

	Vector2 Start;
	Vector2 End = Vector2(1, 1);

	Vector2 Size() const;

	Vector2 Center() const;

	Rect Offset(Vector2 offset) const;

	float Width() const { return End.x - Start.x; }
	float Height() const { return End.y - Start.y; }

	float Width2() const { return Width() * Width(); }
	float Height2() const { return Height() * Height(); }

	bool Overlaps(Rect other) const;
	bool Overlaps(Vector2 offset, Rect other, Vector2 offsetOther) const;

	bool PointInside(Vector2 point) const;

	Vector2 EscapeVector(Vector2 point) const;
	
	Rect RotateAround(Vector2 point, float angle) const;

	Rect Padded(Vector2 padding) const;
};