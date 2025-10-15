#include "Core.h"
#include "PlayerMovementComponent.h"
#include "Camera.h"

void PlayerMovementComponent::OnUpdate(double dt)
{
	Application& app = Application::Get();
	InputManager Input = app.GetWindow()->GetInputManager();

	TransformComponent& transform = GetComponent<TransformComponent>();

	speed += gravity * dt;
	transform.Position += Vector2(0, speed) * (float) dt;

	if (Input.GetKey(Key::Space) == KeyState::Pressed)
		speed = -gravity * 0.5;

	transform.Position.x = sin(Application::Get().GetTime().TimeSinceStart) * 3.0f - 1.5f;
}
