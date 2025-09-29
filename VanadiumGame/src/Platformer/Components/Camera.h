#pragma once
#include "ECS.h"
#include "core/Rendering/Camera.h"

class MovableCameraComponent : public LiveComponent
{
public:
	MovableCameraComponent(unsigned int owner);

	void OnUpdate(double dt) override;
	
	static MovableCameraComponent* Main;
	Camera Camera;
};

inline MovableCameraComponent* MovableCameraComponent::Main = nullptr;