#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

namespace Vanadium
{
	CameraComponent::CameraComponent(EntityRef ref)
		: LiveComponent(ref)
	{
		s_main = this;
	}

	void CameraComponent::OnUpdate(double dt)
	{

	}

	Camera CameraComponent::GetCamera()
	{
		TransformComponent* t = GetComponent<TransformComponent>();

		if (t == nullptr)
			throw "Camera Component needs access to a transform;";

		Camera cam;
		cam.Zoom = Zoom;
		cam.Position = t->Position;
		return cam;
	}
}