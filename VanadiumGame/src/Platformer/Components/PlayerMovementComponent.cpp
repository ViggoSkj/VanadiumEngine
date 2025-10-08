#include "Core.h"
#include "PlayerMovementComponent.h"
#include "Camera.h"
#include "../TransformComponent.h"

void PlayerMovementComponent::OnUpdate(double dt)
{
	Application& app = Application::Get();
	InputManager Input = app.GetWindow()->GetInputManager();

	TransformComponent& transform = GetComponent<TransformComponent>();

	if (Input.Down(Key::W))
		transform.Position.y += 1.0f * (float)dt;
	if (Input.Down(Key::S))
		transform.Position.y -= 1.0f * (float)dt;
	if (Input.Down(Key::A))
		transform.Position.x -= 1.0f * (float)dt;
	if (Input.Down(Key::D))
		transform.Position.x += 1.0f * (float)dt;
}
