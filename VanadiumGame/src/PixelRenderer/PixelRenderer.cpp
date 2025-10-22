#include "PixelRenderer.h"
#include "StaticPixelChunk.h"

PixelRenderer::PixelRenderer()
{

}

void PixelRenderer::OnRender(double dt)
{
	EntityComponentSystem* ECS = Application::Get().GetECS();

	ComponentStore<StaticPixelChunk>* store = ECS->GetComponentStore<StaticPixelChunk>().value_or(nullptr);

	UnorderedVector<StaticPixelChunk>& chunks = store->GetComponents();

	for (int i = 0; i < chunks.size(); i++)
	{
		StaticPixelChunk& chunk = chunks[i];
		chunk.Draw();
	}
}
