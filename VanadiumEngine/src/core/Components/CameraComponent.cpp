#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

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
	TransformComponent* t = GetComponent<TransformComponent>().value_or(nullptr);

	if (t == nullptr)
		throw "Camera Component needs access to a transform;";

	Camera cam;
	cam.Zoom = Zoom;
	cam.Position = t->Position;
	return cam;
}