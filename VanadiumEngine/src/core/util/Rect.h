#pragma once
#include "core/CoreTypes.h"

struct Rect
{
	Rect(Vector2 start = Vector2(0, 0), Vector2 end = Vector2(1, 1))
		: Start(start), End(end) {}

	Vector2 Start;
	Vector2 End = Vector2(1, 1);

	Vector2 Size();

	Vector2 Center();

	Rect Offset(Vector2 offset);

	float Width() const { return End.x - Start.x; }
	float Height() const { return End.y - Start.y; }

	float Width2() const { return Width() * Width(); }
	float Height2() const { return Height() * Height(); }

	bool Overlaps(Rect other);
	bool Overlaps(Vector2 offset, Rect other, Vector2 offsetOther);

	bool PointInside(Vector2 point);

	Vector2 EscapeVector(Vector2 point);
	
	Rect RotateAround(Vector2 point, float angle);

	Rect Padded(Vector2 padding);
};