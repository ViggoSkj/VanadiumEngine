#pragma once
#include "Core.h"
#include "core/Util/Array2D.h"

class PixelBody : public Component
{
public:
	PixelBody(EntityRef ref);

	void AddPixel(u8 x, u8 y, u8 type);

	void SetPixel(u8 x, u8 y, u8 type);

	void UpdateMesh();

	void ResizeBuffers(u32 count);

	void Draw();
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

	u32 m_currentCount = 0;
	u32 m_chunkState = 0;
};