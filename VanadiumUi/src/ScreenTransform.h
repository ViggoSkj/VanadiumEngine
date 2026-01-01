#pragma once
#include "Core.h"

class ScreenTransform : public Component
{
public:
	using Component::Component;

	Rect Surface;
	ScreenTransform* Parent;
};