#pragma once
#include "core/EntityComponentSystem/EntityRef.h"

class StaticPixelChunk;

class ChunkedPixelRefs
{
public:
	ChunkedPixelRefs() = default;
	ChunkedPixelRefs(std::vector<size_t> pixels, StaticPixelChunk* chunk);

	const size_t& operator[](int index) const
	{
		return m_pixels[index];
	}

	bool IsValid();
	size_t Size() const { return m_pixels.size(); }

	StaticPixelChunk* GetChunk();

private:
	std::vector<size_t> m_pixels; // 0 for all
	EntityRef m_chunkEntityRef;
	u32 m_chunkState;
};

class PixelRefs
{
public:
	PixelRefs() = default;
	PixelRefs(std::vector<ChunkedPixelRefs> refs)
		: m_pixelRefs(refs)
	{

	}

	bool IsValid();

	ChunkedPixelRefs* GetChunkedPixelRef(size_t index)
	{
		return &m_pixelRefs[index];
	}

	size_t ChunkCount() const { return m_pixelRefs.size(); }

	size_t Size() const
	{
		size_t size = 0;
		for (int i = 0; i < m_pixelRefs.size(); i++)
		{
			size += m_pixelRefs[i].Size();
		}

		return size;
	}
private:
	std::vector<ChunkedPixelRefs> m_pixelRefs;
};