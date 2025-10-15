#pragma once
#include "Components.h"
#include "core/Util/Rect.h"

class RectCollisionComponent : public Component
{
public:
	Rect Rect;

	UnorderedVector<RectCollisionComponent*> Collisions;
};