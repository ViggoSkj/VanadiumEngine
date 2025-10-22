#pragma once
#include "pch.h"
#include "Core.h"
#include "StaticPixelChunk.h"
#include "PixelRenderer.h"

class PixelWorld : public LiveComponent
{
public:
	static PixelWorld* GetInstance()
	{
		return s_instance->Get().GetComponent<PixelWorld>().value();
	}

	PixelWorld(EntityRef ref)
		: LiveComponent(ref)
	{
		s_instance = new EntityRef(ref); // memory leak?;
	}


	void OnRender(double dt) override;

	void AddPixel(Vector2I position, u8 type);

	LocalChunkPosition ToLocal(Vector2I position);

private:
	static EntityRef* s_instance;

	PixelRenderer m_renderer;

	std::optional<StaticPixelChunk*> FindChunk(Vector2I position);
};