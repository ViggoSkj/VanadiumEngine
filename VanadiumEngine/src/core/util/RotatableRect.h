#pragma once
#include "pch.h"
#include "Rect.h"

struct RotatableRect
{
	RotatableRect(Rect rect, float rotation)
		: Rect(rect), Rotation(rotation)
	{

	}

	Vector2 ToLocal(Vector2 point);
	Vector2 ToGlobal(Vector2 point);
	Vector2 EscapeVector(Vector2 point);
	bool PointInside(Vector2 point);
	std::array<Vector2, 4> Vertices();

	Rect GetAABB();

	Rect Rect;
	float Rotation = 0;
};