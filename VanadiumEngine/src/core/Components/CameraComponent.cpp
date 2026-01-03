#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "ECS.h"

namespace Vanadium
{
	CameraComponent::CameraComponent(Vanadium::ComponentData data)
		: LiveComponent(data)
	{
		CameraComponent::s_active = Vanadium::ECS::CreateHandle(*this);
	}

	void CameraComponent::OnUpdate(double dt)
	{

	}

	Camera CameraComponent::GetCamera()
	{
		TransformComponent* t = GetEntity().GetComponent<TransformComponent>();

		if (t == nullptr)
			throw "Camera Component needs access to a transform;";

		Camera cam;
		cam.Zoom = Zoom;
		cam.Position = t->Position;
		return cam;
	}
}