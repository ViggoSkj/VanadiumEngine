#include "CameraMovementComponent.h"
#include "Components.h"

CameraMovementComponent::CameraMovementComponent(EntityRef ref)
	: LiveComponent(ref)
{
}

void CameraMovementComponent::OnUpdate(double dt)
{
	GLFWwindow* glfwWindow = Application::Get().GetWindow()->GetGLFWwindow().get();

	const InputManager& Input = Application::Get().GetWindow()->GetInputManager();
	EntityComponentSystem* ECS = Application::Get().GetECS();
	SceneManager* sceneManager = Application::Get().GetSceneManager();

	CameraComponent& camera = *GetComponent<CameraComponent>();
	TransformComponent& transform = *GetComponent<TransformComponent>();

	if (Input.GetKey(Key::R) == KeyState::Pressed)
	{
		sceneManager->UnloadScene(ECS->FindEntity(GetOwnerId())->GetOwner());
		sceneManager->LoadScene(ECS->FindEntity(GetOwnerId())->GetOwner());
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
