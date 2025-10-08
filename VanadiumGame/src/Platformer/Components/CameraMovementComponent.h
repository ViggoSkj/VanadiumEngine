#pragma once
#include "ECS.h"
#include "core/Rendering/Camera.h"

class CameraMovementComponent : public LiveComponent
{
public:
	CameraMovementComponent(unsigned int owner);

	void OnUpdate(double dt) override;
};