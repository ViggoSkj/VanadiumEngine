#include "pch.h"
#include "core/Math.h"
#include "Rect.h"

Vector2 Rect::Size()
{
	// Ensure size is always positive (width/height)
	return { End.x - Start.x, End.y - Start.y };
}

Vector2 Rect::Center()
{
	return Start + (End - Start) / 2.0f;
}

Rect Rect::Offset(Vector2 offset)
{
	return Rect(Start + offset, End + offset);
}

bool Rect::Overlaps(Rect other)
{
	if (other.Start.x > End.x)
		return false;
	if (other.End.x < Start.x)
		return false;

	if (other.Start.y > End.y)
		return false;
	if (other.End.y < Start.y)
		return false;

	return true;
}

bool Rect::Overlaps(Vector2 offset, Rect other, Vector2 offsetOther)
{
	if (other.Start.x + offsetOther.x > End.x + offset.x)
		return false;
	if (other.End.x + offsetOther.x < Start.x + offset.x)
		return false;

	if (other.Start.y + offsetOther.y > End.y + offset.y)
		return false;
	if (other.End.y + offsetOther.y < Start.y + offset.y)
		return false;

	return true;
}

bool Rect::PointInside(Vector2 point)
{
	return point.x >= Start.x && point.x <= End.x
		&& point.y >= Start.y && point.y <= End.y;
}


Vector2 Rect::EscapeVector(Vector2 point)
{
	if (!PointInside(point))
		return { 0,0 };

	Vector2 escape = { 0, 0 };

	if (point.x - Start.x < End.x - point.x)
		escape.x = Start.x - point.x;
	else
		escape.x = End.x - point.x;

	if (point.y - Start.y < End.y - point.y)
		escape.y = Start.y - point.y;
	else
		escape.y = End.y - point.y;

	return escape;
}

Rect Rect::RotateAround(Vector2 point, float angle)
{
	// Preserve axis-aligned semantics: keep Start as min corner and End as max corner
	Vector2 newCenter = Math::RotatePoint(Center(), point, angle);
	Vector2 halfSize = Size() / 2.0f;

	Vector2 newStart = newCenter - halfSize;
	Vector2 newEnd = newCenter + halfSize;

	// Enforce lower-left and top-right ordering without relying on Math::Min/Max
	Vector2 minCorner(
		newStart.x < newEnd.x ? newStart.x : newEnd.x,
		newStart.y < newEnd.y ? newStart.y : newEnd.y);
	Vector2 maxCorner(
		newStart.x > newEnd.x ? newStart.x : newEnd.x,
		newStart.y > newEnd.y ? newStart.y : newEnd.y);

	return Rect(minCorner, maxCorner);
}

Rect Rect::Padded(Vector2 padding)
{
	return Rect(Start - padding, End + padding);
}