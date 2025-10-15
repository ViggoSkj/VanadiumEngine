#pragma once
#include "pch.h"
#include "ECS.h"

class PlayerMovementComponent : public LiveComponent
{
public:
	PlayerMovementComponent(unsigned int owner)
		: LiveComponent(owner) { }

	void OnUpdate(double dt) override;

private:
	float speed = 0;
	float gravity = -9.82;
};