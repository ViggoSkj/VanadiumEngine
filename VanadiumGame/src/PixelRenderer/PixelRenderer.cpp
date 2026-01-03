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
	Vanadium::EntityComponentSystem* ECS = Application::Get().GetECS();

	// chunks
	Vanadium::ComponentStore<StaticPixelChunk>* chunkStore = ECS->GetComponentStore<StaticPixelChunk>();
	UnorderedVector<StaticPixelChunk>& chunks = chunkStore->GetComponents();
	for (int i = 0; i < chunks.size(); i++)
	{
		StaticPixelChunk& chunk = chunks[i];
		chunk.Draw();
	}

	// bodies
	Vanadium::ComponentStore<PixelBody>* bodiesStore = ECS->GetComponentStore<PixelBody>();
	UnorderedVector<PixelBody>& bodies = bodiesStore->GetComponents();
	for (int i = 0; i < bodies.size(); i++)
	{
		PixelBody& body = bodies[i];
		body.Draw();
	}
}

void PixelRenderer::OnRenderDebug(double dt)
{
	Vanadium::EntityComponentSystem* ECS = Application::Get().GetECS();

	Vanadium::ComponentStore<PixelCollisionComponent>* collidersStore = ECS->GetComponentStore<PixelCollisionComponent>();
	UnorderedVector<PixelCollisionComponent>& colliders = collidersStore->GetComponents();
	for (int i = 0; i < colliders.size(); i++)
	{
		PixelCollisionComponent& collider = colliders[i];
		TransformComponent& t = *collider.GetEntity().GetComponent<TransformComponent>();

		for (Rect rect : collider.GetCollisionRects())
		{
			//ShapeRenderer::Get()->FillRect(Math::RotatePoint(rect.Center(), t.RotationAngle()) + t.Position, rect.Size(), t.RotationAngle(), {1.0, 0.0, 1.0, 0.5});
		}
	}
}