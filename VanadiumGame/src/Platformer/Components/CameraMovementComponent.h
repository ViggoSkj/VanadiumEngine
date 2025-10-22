#pragma once
#include "ECS.h"
#include "core/Rendering/Camera.h"

class CameraMovementComponent : public LiveComponent
{
public:
	CameraMovementComponent(EntityRef ref);

	void OnUpdate(double dt) override;
};