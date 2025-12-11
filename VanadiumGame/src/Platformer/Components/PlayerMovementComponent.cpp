#include "Core.h"
#include "PlayerMovementComponent.h"
#include "Camera.h"
#include "PixelRenderer/PixelWorld.h"

void PlayerMovementComponent::OnUpdate(double dt)
{
	Application& app = Application::Get();
	InputManager Input = app.GetWindow()->GetInputManager();

	TransformComponent& transform = *GetComponent<TransformComponent>().value();

	if (Input.Down(Key::W))
		transform.Position.y += Speed * dt;
	if (Input.Down(Key::S))
		transform.Position.y -= Speed * dt;
	if (Input.Down(Key::A))
		transform.Position.x -= Speed * dt;
	if (Input.Down(Key::D))
		transform.Position.x += Speed * dt;


	RectCollisionComponent& collision = *GetComponent<RectCollisionComponent>().value();
	PixelRefs refs = PixelWorld::GetInstance()->RectCast(collision.WorldRect());

	for (int i = 0; i < refs.ChunkCount(); i++)
	{
		PixelWorld::GetInstance()->RemovePixels(*refs.GetChunkedPixelRef(i));
	}
}
