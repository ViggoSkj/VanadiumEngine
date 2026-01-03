#pragma once
#include "Core.h"

class ScreenTransform : public Component
{
public:
	using Component::Component;

	Rect Surface;
	Vanadium::ComponentHandle<ScreenTransform> Parent;

	Matrix4x4 ModelMatrix();
};