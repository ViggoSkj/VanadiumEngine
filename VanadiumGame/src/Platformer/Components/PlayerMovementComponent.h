#pragma once
#include "pch.h"
#include "ECS.h"

class PlayerMovementComponent : public LiveComponent
{
public:
	using LiveComponent::LiveComponent;

	void OnUpdate(double dt) override;

	float Speed = 3.5;
private:
	float gravity = -9.82;
};