#include "pch.h"
#include "RectI.H"

bool RectI::Inside(Vector2 point)
{
	return start.x < point.x && point.x < end.x &&
		start.y < point.y && point.y < end.y;
}