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
	Camera cam;
	cam.Zoom = Zoom;
	cam.Position = GetComponent<TransformComponent>().value()->Position;
	return cam;
}