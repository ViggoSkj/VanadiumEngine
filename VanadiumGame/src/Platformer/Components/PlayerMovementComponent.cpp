#include "Core.h"
#include "PlayerMovementComponent.h"
#include "Camera.h"
#include "PixelRenderer/PixelWorld.h"
#include "core/ShapeRenderer/ShapeRenderer.h"

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




	Vector2 Size = { std::cos(app.GetTime().TimeSinceStart) * 0.5 + 0.5, std::sin(app.GetTime().TimeSinceStart) * 0.5  + 0.5};

	ShapeRenderer::Get()->FillRect(transform.Position, Size, 0, { 1.0, 1.0, 1.0, 0.5 });

	for (int i = 0; i < refs.ChunkCount(); i++)
	{
		PixelWorld::GetInstance()->RemovePixels(*refs.GetChunkedPixelRef(i));
	}
}
