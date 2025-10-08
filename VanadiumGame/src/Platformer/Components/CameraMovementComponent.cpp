#include "CameraMovementComponent.h"

CameraMovementComponent::CameraMovementComponent(unsigned int owner)
	: LiveComponent(owner)
{
}

void CameraMovementComponent::OnUpdate(double dt) 
{
	GLFWwindow* glfwWindow = Application::Get().GetWindow()->GetGLFWwindow().get();

	const InputManager& Input = Application::Get().GetWindow()->GetInputManager();
	EntityComponentSystem* ECS = Application::Get().GetECS();
	SceneManager* sceneManager = Application::Get().GetSceneManager();

	Camera& camera = GetComponent<CameraComponent>().GetCamera();;

	if (Input.GetKey(Key::R) == KeyState::Pressed)
	{
		sceneManager->UnloadScene(ECS->FindEntity(GetOwnerId()).GetOwner());
		sceneManager->LoadScene(ECS->FindEntity(GetOwnerId()).GetOwner());
	}

	if (Input.Down(Key::Q))
		camera.Zoom += 1.0f * (float)dt * camera.Zoom;
	if (Input.Down(Key::E))
		camera.Zoom -= 1.0f * (float)dt * camera.Zoom;
}
