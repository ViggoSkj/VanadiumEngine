#include "pch.h"
#include "Rect.h"

Vector2 Rect::Size()
{
	return Start - End;
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