#pragma once
#include "Core.h"
#include "core/Util/Array2D.h"
#include "PixelSoa.h"
#include "../PhysicsTest/Rigidbody.h"

class PixelBody : public Component
{
public:
	inline static float PixelDensity = 100; // 1000 kg/m^2 (like water)

	PixelBody(EntityRef ref);

	void AddPixel(i32 x, i32 y, u8 type);

	void SetPixel(i32 x, i32 y, u8 type);

	void UpdateMesh();

	void ResizeBuffers(u32 count);

	void Draw();

	PixelSoa GetSoa() { return m_pixelSoa; }

	Vector2 LinearVelocity;
	float AngularVelocity;
private:
	PixelSoa m_pixelSoa;

	bool m_buffersUpToDate = true;
	VertexBuffer m_xBuffer;
	VertexBuffer m_yBuffer;
	VertexBuffer m_typeBuffer;

	VertexArray m_vao;
	Shader m_shader;

	u32 m_currentCount = 0;
	u32 m_chunkState = 0;
};