#pragma
#include "pch.h"
#include "core/EntityComponentSystem/LiveComponent/LiveComponent.h"
#include "core/Rendering/Camera.h"

class CameraComponent : public LiveComponent
{
public:
	static std::optional<CameraComponent*> GetMain()
	{ 
		if (s_main == nullptr)
			return std::nullopt;

		return s_main;
	};

	CameraComponent(unsigned int owner);

	void OnUpdate(double dt) override;

	Camera GetCamera();

	float Zoom = 1.0;
private:
	static CameraComponent* s_main;
};

inline CameraComponent* CameraComponent::s_main = nullptr;