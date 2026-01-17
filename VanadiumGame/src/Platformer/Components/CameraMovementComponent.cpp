#include "CameraMovementComponent.h"
#include "Core.h"

void CameraMovementComponent::OnUpdate(double dt)
{
	const InputManager& Input = Application::Get().GetWindow()->GetInputManager();
	SceneManager* sceneManager = Application::Get().GetSceneManager();

	CameraComponent& camera = *GetEntity().GetComponent<CameraComponent>();
	TransformComponent& transform = *GetEntity().GetComponent<TransformComponent>();

	if (Input.GetKey(Key::R) == KeyState::Pressed)
	{
		sceneManager->ReloadScene(GetEntity().GetSceneRef().GetId());
	}

	if (EnableMove && !MoveToTarget)
	{
		if (Input.Down(Key::W))
			transform.Position.y += 1.0f * (float)dt / camera.Zoom;
		if (Input.Down(Key::S))
			transform.Position.y -= 1.0f * (float)dt / camera.Zoom;
		if (Input.Down(Key::A))
			transform.Position.x -= 1.0f * (float)dt / camera.Zoom;
		if (Input.Down(Key::D))
			transform.Position.x += 1.0f * (float)dt / camera.Zoom;
	}
	else if (MoveToTarget)
	{
		Vector2 targetPosition = Target.Get().GetComponent<TransformComponent>()->Position;
		transform.Position = glm::mix(transform.Position, targetPosition, 2.0f * dt);
	}

	if (Input.Down(Key::Q))
		camera.Zoom += 1.0f * (float)dt * camera.Zoom;
	if (Input.Down(Key::E))
		camera.Zoom -= 1.0f * (float)dt * camera.Zoom;
}
