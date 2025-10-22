#pragma once
#include "pch.h"
#include "ECS.h"

class PlayerMovementComponent : public LiveComponent
{
public:
	PlayerMovementComponent(EntityRef ref)
		: LiveComponent(ref) { }

	void OnUpdate(double dt) override;

private:
	float speed = 0;
	float gravity = -9.82;
};