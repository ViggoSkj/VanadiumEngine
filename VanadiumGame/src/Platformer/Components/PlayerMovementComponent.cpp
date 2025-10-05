#include "Core.h"
#include "PlayerMovementComponent.h"
#include "Camera.h"

void PlayerMovementComponent::OnUpdate(double dt)
{
	Application& app = Application::Get();
	InputManager Input = app.GetWindow()->GetInputManager();

	Camera cam = MovableCameraComponent::Main->Camera;
	
	if (Input.Down(Key::W))
		cam.Position.y += 1.0f * (float)dt / cam.Zoom;
	if (Input.Down(Key::S))
		cam.Position.y -= 1.0f * (float)dt / cam.Zoom;
	if (Input.Down(Key::A))
		cam.Position.x -= 1.0f * (float)dt / cam.Zoom;
	if (Input.Down(Key::D))
		cam.Position.x += 1.0f * (float)dt / cam.Zoom;
}
