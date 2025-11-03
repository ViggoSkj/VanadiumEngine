#include "PixelWorld.h"

EntityRef* PixelWorld::s_instance = nullptr;

void PixelWorld::OnRender(double dt)
{
	m_renderer.OnRender(dt);
}
 
void PixelWorld::OnUpdate(double dt)
{
	static float changesToMakeBuffer = 0;
	float changesPerSecond = 0;

	changesToMakeBuffer += dt * changesPerSecond;

	u32 changesToMake = changesToMakeBuffer;

	if (changesToMake < 1)
		return;

	changesToMakeBuffer -= changesToMake;

	while (changesToMake > 0)
	{
		i32 x = rand() % 300;
		i32 y = rand() % 300;
		u8 t = rand() % 3;

		SetPixel({ x, y }, t);

		changesToMake--;
	}
}

void PixelWorld::AddPixel(Vector2I position, u8 type)
{
	Vector2I chunkPosition = position / 256;
	std::optional<StaticPixelChunk*> chunkOpt = FindChunk(chunkPosition);
	StaticPixelChunk& chunk = GetChunk(chunkPosition);
	chunk.AddPixel(ToLocal(position), type);
}

void PixelWorld::SetPixel(Vector2I position, u8 type)
{
	Vector2I chunkPosition = position / 256;
	std::optional<StaticPixelChunk*> chunkOpt = FindChunk(chunkPosition);
	StaticPixelChunk& chunk = GetChunk(chunkPosition);
	chunk.SetPixel(ToLocal(position), type);
}

void PixelWorld::RemovePixels(ChunkedPixelRefs& refs)
{
	StaticPixelChunk* chunk = refs.GetChunk();
	chunk->RemovePixels(refs);
}

PixelRefs PixelWorld::RectCast(Rect cast)
{
	UnorderedVector<StaticPixelChunk>& chunks = GetChunks();
	UnorderedVector<StaticPixelChunk*> overlapingChunks;
	
	for (int i = 0; i < chunks.size(); i++)
	{
		if (cast.Overlaps(chunks[i].GetRect()))
			overlapingChunks.push_back(&chunks[i]);
	}

	std::vector<ChunkedPixelRefs> refs;

	for (int i = 0; i < overlapingChunks.size(); i++)
	{
		refs.push_back(overlapingChunks[i]->RectCast(cast));
	}

	return PixelRefs(std::move(refs));
}

LocalChunkPosition PixelWorld::ToLocal(Vector2I position)
{
	LocalChunkPosition p;
	p.x = position.x;
	p.y = position.y;
	return p;
}

StaticPixelChunk* PixelWorld::CreateChunk(Vector2I position)
{
	EntityComponentSystem* ECS = Application::Get().GetECS();
	EntityRef e = GetEntity().GetScene().CreateEntity();
	StaticPixelChunk* chunk = e.Get().AddComponent<StaticPixelChunk>();
	chunk->Position = position;
	return chunk;
}

StaticPixelChunk& PixelWorld::GetChunk(Vector2I position)
{
	std::optional<StaticPixelChunk*> chunkOpt = FindChunk(position);
	StaticPixelChunk* chunk;

	if (!chunkOpt.has_value())
	{
		chunk = CreateChunk(position);
	}
	else
	{
		chunk = chunkOpt.value();
	}
	return *chunk;
}

std::optional<StaticPixelChunk*> PixelWorld::FindChunk(Vector2I position)
{
	i32 chunkX = position.x / 32;
	i32 chunkY = position.y / 32;

	UnorderedVector<StaticPixelChunk>& chunks = GetChunks();

	for (int i = 0; i < chunks.size(); i++)
	{
		StaticPixelChunk& chunk = chunks[i];
		if (chunk.Position == position)
			return &chunk;
	}

	return std::nullopt;
}

UnorderedVector<StaticPixelChunk>& PixelWorld::GetChunks()
{
	ComponentStore<StaticPixelChunk>* store = Application::Get().GetECS()->GetComponentStore<StaticPixelChunk>().value_or(nullptr);
	return store->GetComponents();
}
