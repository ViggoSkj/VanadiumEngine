#include "Core.h"
#include "PlayerMovementComponent.h"
#include "Camera.h"
#include "PixelRenderer/PixelWorld.h"
#include "core/ShapeRenderer/ShapeRenderer.h"
#include "PhysicsTest/Rigidbody.h"
#include "PixelRenderer/PixelCollisionComponent.h"

void PlayerMovementComponent::OnUpdate(double dt)
{
	Application& app = Application::Get();
	InputManager Input = app.GetWindow()->GetInputManager();

	TransformComponent& transform = *GetComponent<TransformComponent>();

	Rigidbody* rb = GetComponent<Rigidbody>();

	if (rb != nullptr)
	{
		if (Input.Down(Key::W))
			rb->LinearVelocity.y += Speed * dt;
		if (Input.Down(Key::S))
			rb->LinearVelocity.y -= Speed * dt;
		if (Input.Down(Key::A))
			rb->LinearVelocity.x -= Speed * dt;
		if (Input.Down(Key::D))
			rb->LinearVelocity.x += Speed * dt;
	}
	else
	{
		if (Input.Down(Key::W))
			transform.Position.y += Speed * dt;
		if (Input.Down(Key::S))
			transform.Position.y -= Speed * dt;
		if (Input.Down(Key::A))
			transform.Position.x -= Speed * dt;
		if (Input.Down(Key::D))
			transform.Position.x += Speed * dt;
	}



	RectCollisionComponent* collision = GetComponent<RectCollisionComponent>();

	if (collision != nullptr)
	{
		PixelRefs refs = PixelWorld::GetInstance()->RectCast(collision->WorldRect());
		for (int i = 0; i < refs.ChunkCount(); i++)
		{
			PixelWorld::GetInstance()->RemovePixels(*refs.GetChunkedPixelRef(i));
		}
	}
}
