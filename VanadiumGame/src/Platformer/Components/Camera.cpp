#include "Camera.h"

MovableCameraComponent::MovableCameraComponent(unsigned int owner)
	: LiveComponent(owner)
{
	MovableCameraComponent::Main = this;
}

void MovableCameraComponent::OnUpdate(double dt) 
{
	GLFWwindow* glfwWindow = Application::Get().GetWindow().GetGLFWwindow().get();

	const InputManager& Input = Application::Get().GetWindow().GetInputManager();
	EntityComponentSystem &ECS = Application::Get().GetECS();
	SceneManager& sceneManager = Application::Get().GetSceneManager();

	if (Input.Down(Key::R))
		sceneManager.UnloadScene(ECS.FindEntity(GetOwnerId()).GetOwner());

	if (Input.Down(Key::W))
		this->Camera.Position.y += 1.0f * (float)dt / this->Camera.Zoom;
	if (Input.Down(Key::S))
		this->Camera.Position.y -= 1.0f * (float)dt / this->Camera.Zoom;
	if (Input.Down(Key::A))
		this->Camera.Position.x -= 1.0f * (float)dt / this->Camera.Zoom;
	if (Input.Down(Key::D))
		this->Camera.Position.x += 1.0f * (float)dt / this->Camera.Zoom;
	if (Input.Down(Key::Q))
		this->Camera.Zoom += 1.0f * (float)dt * this->Camera.Zoom;
	if (Input.Down(Key::E))
		this->Camera.Zoom -= 1.0f * (float)dt * this->Camera.Zoom;
}
