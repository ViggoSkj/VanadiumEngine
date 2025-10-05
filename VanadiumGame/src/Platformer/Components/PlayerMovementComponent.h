#pragma once
#include "ECS.h"

class PlayerMovementComponent : public LiveComponent
{
public:
	PlayerMovementComponent(unsigned int owner)
		: LiveComponent(owner) { }

	void OnUpdate(double dt) override;

private:
};