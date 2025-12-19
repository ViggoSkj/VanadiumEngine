#pragma once
#include "Core.h"

class PixelRenderer
{
public:
	PixelRenderer();

	void OnRender(double dt);
	void OnRenderDebug(double dt);
};