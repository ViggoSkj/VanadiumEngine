#pragma once
#include "Application.h"

/*
What is needed:
- some sort of sprite renderign
- some sort of collision and physics
- some sort of camera following
*/

class PlatformerLayer : public ApplicationLayer
{
public:
	PlatformerLayer();

	void OnUpdate(double dt) override;
	void OnRender(double dt) override;

private:
};