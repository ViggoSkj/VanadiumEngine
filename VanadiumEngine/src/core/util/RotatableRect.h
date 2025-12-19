#pragma once
#include "pch.h"
#include "Rect.h"

struct RotatableRect
{
	RotatableRect(Rect rect, float rotation)
		: Rect(rect), Rotation(rotation)
	{

	}

	std::array<Vector2, 4> Vertices();

	Rect Rect;
	float Rotation = 0;
};