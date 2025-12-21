#include "PixelRenderer.h"
#include "StaticPixelChunk.h"
#include "PixelBody.h"
#include "PixelCollisionComponent.h"
#include "core/ShapeRenderer/ShapeRenderer.h"
#include "core/Math.h"

PixelRenderer::PixelRenderer()
{

}

void PixelRenderer::OnRender(double dt)
{
	EntityComponentSystem* ECS = Application::Get().GetECS();

	// chunks
	ComponentStore<StaticPixelChunk>* chunkStore = ECS->GetComponentStore<StaticPixelChunk>().value_or(nullptr);
	UnorderedVector<StaticPixelChunk>& chunks = chunkStore->GetComponents();
	for (int i = 0; i < chunks.size(); i++)
	{
		StaticPixelChunk& chunk = chunks[i];
		chunk.Draw();
	}

	// bodies
	ComponentStore<PixelBody>* bodiesStore = ECS->GetComponentStore<PixelBody>().value_or(nullptr);
	UnorderedVector<PixelBody>& bodies = bodiesStore->GetComponents();
	for (int i = 0; i < bodies.size(); i++)
	{
		PixelBody& body = bodies[i];
		body.Draw();
	}
}

void PixelRenderer::OnRenderDebug(double dt)
{
	EntityComponentSystem* ECS = Application::Get().GetECS();

	ComponentStore<PixelCollisionComponent>* collidersStore = ECS->GetComponentStore<PixelCollisionComponent>().value_or(nullptr);
	UnorderedVector<PixelCollisionComponent>& colliders = collidersStore->GetComponents();
	for (int i = 0; i < colliders.size(); i++)
	{
		PixelCollisionComponent& collider = colliders[i];
		TransformComponent& t = *collider.GetComponent<TransformComponent>().value_or(nullptr);

		for (Rect rect : collider.GetCollisionRects())
		{
			//ShapeRenderer::Get()->FillRect(Math::RotatePoint(rect.Center(), t.RotationAngle()) + t.Position, rect.Size(), t.RotationAngle(), {1.0, 0.0, 1.0, 0.5});
		}
	}
}