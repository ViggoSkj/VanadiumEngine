#include "PixelRenderer.h"
#include "StaticPixelChunk.h"
#include "PixelBody.h"

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
		//chunk.Draw();
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
