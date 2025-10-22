#include "PixelWorld.h"

EntityRef* PixelWorld::s_instance = nullptr;

void PixelWorld::OnRender(double dt)
{
	m_renderer.OnRender(dt);
}

void PixelWorld::AddPixel(Vector2I position, u8 type)
{
	Vector2I chunkPosition = position / 256;
	std::optional<StaticPixelChunk*> chunkOpt = FindChunk(chunkPosition);
	StaticPixelChunk* chunk;

	if (!chunkOpt.has_value())
	{
		EntityComponentSystem* ECS = Application::Get().GetECS();

		EntityRef e = GetEntity().GetScene().CreateEntity();
		chunk = e.Get().AddComponent<StaticPixelChunk>();
		chunk->Position = chunkPosition;
	}
	else
	{
		chunk = chunkOpt.value();
	}

	LocalChunkPosition localPosition = ToLocal(position);
	chunk->AddPixel(localPosition, type);
}

LocalChunkPosition PixelWorld::ToLocal(Vector2I position)
{
	LocalChunkPosition p;
	p.x = position.x;
	p.y = position.y;
	return p;
}

std::optional<StaticPixelChunk*> PixelWorld::FindChunk(Vector2I position)
{
	i32 chunkX = position.x / 32;
	i32 chunkY = position.y / 32;

	ComponentStore<StaticPixelChunk>* store = Application::Get().GetECS()->GetComponentStore<StaticPixelChunk>().value_or(nullptr);
	UnorderedVector<StaticPixelChunk>& chunks = store->GetComponents();


	for (int i = 0; i < chunks.size(); i++)
	{
	StaticPixelChunk& chunk = chunks[i];
		if (chunk.Position == position)
			return &chunk;
	}

	return std::nullopt;
}