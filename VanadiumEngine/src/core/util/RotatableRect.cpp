#include "pch.h"
#include "RotatableRect.h"
#include "core/Math.h"

Vector2 RotatableRect::ToLocal(Vector2 point)
{
	return Math::RotatePoint(point, Rect.Center(), -Rotation);
}

Vector2 RotatableRect::ToGlobal(Vector2 point)
{
	return Math::RotatePoint(point, Rect.Center(), Rotation);
}

Vector2 RotatableRect::EscapeVector(Vector2 point)
{
	Vector2 local = ToLocal(point);
	Vector2 localEscape = Rect.EscapeVector(local);
	return Math::RotatePoint(localEscape, Rotation);
}

std::array<Vector2, 4> RotatableRect::Vertices()
{
	Vector2 center = Rect.Center();

	return {
		Math::RotatePoint(Vector2(Rect.Start.x, Rect.End.y), center, Rotation),
		Math::RotatePoint(Rect.End, center, Rotation),
		Math::RotatePoint(Vector2(Rect.End.x,  Rect.Start.y), center, Rotation),
		Math::RotatePoint(Rect.Start, center, Rotation)
	};
}

bool RotatableRect::PointInside(Vector2 point)
{
	Vector2 local = ToLocal(point);
	return Rect.PointInside(local);
}

Rect RotatableRect::GetAABB()
{
	Vector2 center = Rect.Center();
	Vector2 halfSize = (Rect.End - Rect.Start) / 2.0f;

	float maxExtent = glm::max(glm::abs(halfSize.x), glm::abs(halfSize.y)) * 1.42f;

	return ::Rect(Vector2(center.x - maxExtent, center.y - maxExtent),
		Vector2(center.x + maxExtent, center.y + maxExtent));
}