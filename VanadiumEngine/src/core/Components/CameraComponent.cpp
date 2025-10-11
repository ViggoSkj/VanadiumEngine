#include "CameraComponent.h"

CameraComponent::CameraComponent(unsigned int owner)
	: LiveComponent(owner)
{
	s_main = this;
}

void CameraComponent::OnUpdate(double dt)
{

}
