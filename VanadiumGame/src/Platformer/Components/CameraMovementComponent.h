#pragma once
#include "ECS.h"
#include "core/Rendering/Camera.h"

class CameraMovementComponent : public LiveComponent
{
public:
	using LiveComponent::LiveComponent;

	void OnUpdate(double dt) override;

	bool EnableMove = false;
	bool MoveToTarget = false;
	EntityRef Target;
};