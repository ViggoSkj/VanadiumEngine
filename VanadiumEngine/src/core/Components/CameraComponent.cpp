#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

CameraComponent::CameraComponent(unsigned int owner)
	: LiveComponent(owner)
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
	cam.Position = GetComponent<TransformComponent>().Position;
	return cam;
}