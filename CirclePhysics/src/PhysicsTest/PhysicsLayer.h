#pragma once
#include "Application.h"

class PhysicsLayer : public ApplicationLayer
{
public:
	void OnUpdate(double dt) override;

	float Gravity = 9.82f;
};