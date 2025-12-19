#include "pch.h"
#include "RotatableRect.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

std::array<Vector2, 4> RotatableRect::Vertices()
{
	Vector2 center = Rect.Start + (Rect.End - Rect.Start) / 2.0f;

	Vector2 v1 = Vector2(Rect.Start.x, Rect.Start.y) - center;
	Vector2 v2 = Vector2(Rect.Start.x, Rect.End.y) - center;
	Vector2 v3 = Vector2(Rect.End.x, Rect.End.y) - center;
	Vector2 v4 = Vector2(Rect.End.x, Rect.Start.y) - center;
}