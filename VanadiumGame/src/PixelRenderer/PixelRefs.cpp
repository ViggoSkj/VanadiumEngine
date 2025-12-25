#include "PixelRefs.h"
#include "StaticPixelChunk.h"
#include "core/EntityComponentSystem/Entity.h"

bool PixelRefs::IsValid()
{
	for (int i = 0; i < m_pixelRefs.size(); i++)
		if (!(m_pixelRefs[i].IsValid()))
			return false;

	return true;
}


ChunkedPixelRefs::ChunkedPixelRefs(std::vector<size_t> pixels, StaticPixelChunk* chunk)
	: m_pixels(pixels), m_chunkEntityRef(chunk->GetEntityRef()), m_chunkState(chunk->GetChunkState())
{

}

bool ChunkedPixelRefs::IsValid()
{
	return m_chunkEntityRef.Get().GetComponent<StaticPixelChunk>()->GetChunkState() == m_chunkState;
}

StaticPixelChunk* ChunkedPixelRefs::GetChunk()
{
	return m_chunkEntityRef.Get().GetComponent<StaticPixelChunk>();
}
