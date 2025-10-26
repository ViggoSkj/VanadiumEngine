#pragma once
#include "Core.h"
#include "core/Util/Array2D.h"
#include "core/Util/Rect.h"
#include "PixelRefs.h"

struct LocalChunkPosition
{
	u8 x;
	u8 y;
};

class StaticPixelChunk : public Component
{
public:
	inline const static float ChunkSize = 10.0;
	static const u32 Size = 256;
	StaticPixelChunk(EntityRef ref);

	void AddPixel(LocalChunkPosition position, u8 type);
	void AddPixel(u8 x, u8 y, u8 type);

	void SetPixel(LocalChunkPosition position, u8 type);
	void SetPixel(u8 x, u8 y, u8 type);

	void RemovePixels(ChunkedPixelRefs& refs);

	void Draw();

	ChunkedPixelRefs RectCast(Rect cast);

	Rect GetRect();

	u32 GetChunkState() const { return m_chunkState; }

	Vector2I Position;
private:

	UnorderedVector<u8> m_soa_x;
	UnorderedVector<u8> m_soa_y;
	UnorderedVector<u8> m_soa_type;

	bool m_buffersUpToDate = true;
	VertexBuffer m_xBuffer;
	VertexBuffer m_yBuffer;
	VertexBuffer m_typeBuffer;

	VertexArray m_vao;
	Shader m_shader;

	u32 m_chunkState = 0;
};