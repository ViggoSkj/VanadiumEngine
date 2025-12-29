#pragma once
#include "pch.h"
#include "Core.h"
#include "StaticPixelChunk.h"
#include "PixelRenderer.h"

class PixelWorld : public LiveComponent
{
public:
	static const inline float PixelSize = 10.0f/256.0f;

	static PixelWorld* GetInstance()
	{
		return s_instance->Get().GetComponent<PixelWorld>();
	}

	PixelWorld(EntityRef ref)
		: LiveComponent(ref)
	{
		s_instance = new EntityRef(ref); // memory leak?;
	}


	void OnRender(double dt) override;

	void OnUpdate(double dt) override;

	void AddPixel(Vector2I position, u8 type);
	void SetPixel(Vector2I position, u8 type);

	void RemovePixels(ChunkedPixelRefs& refs);

	PixelRefs RectCast(Rect cast);

	LocalChunkPosition ToLocal(Vector2I position);
private:
	static EntityRef* s_instance;

	PixelRenderer m_renderer;

	StaticPixelChunk* CreateChunk(Vector2I position);
	StaticPixelChunk& GetChunk(Vector2I position);
	std::optional<StaticPixelChunk*> FindChunk(Vector2I position);
	UnorderedVector<StaticPixelChunk>& GetChunks();
};