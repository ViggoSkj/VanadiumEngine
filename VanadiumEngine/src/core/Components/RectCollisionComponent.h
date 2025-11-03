#pragma once
#include "Components.h"
#include "core/Util/Rect.h"

class RectCollisionComponent : public Component
{
public:

	void SetSize(float width, float height)
	{
		Rect = { Vector2(-width/2.0, -height/2.0), Vector2(width/2.0, height/2.0)};
	}

	Rect Rect;

	UnorderedVector<RectCollisionComponent*> Collisions;
};