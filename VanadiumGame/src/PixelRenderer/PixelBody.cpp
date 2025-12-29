#include "PixelBody.h"
#include "StaticPixelChunk.h"
#include "PixelCollisionComponent.h"
#include "PixelWorld.h"
#include "core/Util/StringHash.h"
#include "Rendering.h"
#include "Util.h"

PixelBody::PixelBody(EntityRef ref)
	: Component(ref),
	m_shader(Application::Get().GetAssetManager()->GetFileAsset<Vanadium::ShaderCodeAsset>("res/shaders/pixelbody.shader")->CreateShader().value()),
	m_pixelSoa(),
	m_pixelMeshHandle(Vanadium::Rendering::CreateMesh(Vanadium::Util::SquareMeshData(PixelWorld::PixelSize))),
	m_currentCount(1000)
{
	UpdateMesh();
}

void PixelBody::UpdateMesh()
{
	using namespace Vanadium::Rendering;

	m_vao = CreateVertexArray(m_pixelMeshHandle);

	m_vao.AddVertexBuffer({ Vanadium::GLVertexAttribute(GL_INT, 1, GL_FALSE) }, m_xBuffer, 1, 1);
	m_vao.AddVertexBuffer({ Vanadium::GLVertexAttribute(GL_INT, 1, GL_FALSE) }, m_yBuffer, 2, 1);
	m_vao.AddVertexBuffer({ Vanadium::GLVertexAttribute(GL_UNSIGNED_BYTE, 1, GL_TRUE) }, m_typeBuffer, 3, 1);
	
	m_xBuffer.SetVertecies(nullptr, sizeof(float) * m_currentCount, GL_DYNAMIC_DRAW);
	m_yBuffer.SetVertecies(nullptr, sizeof(float) * m_currentCount, GL_DYNAMIC_DRAW);
	m_typeBuffer.SetVertecies(nullptr, m_currentCount, GL_DYNAMIC_DRAW);

	m_shader.SetUniformFloat("u_size"_id, PixelWorld::PixelSize);
}

void PixelBody::ResizeBuffers(u32 count)
{
	m_xBuffer.SetVertecies(nullptr, sizeof(i32) * count, GL_DYNAMIC_DRAW);

	m_yBuffer.SetVertecies(nullptr, sizeof(i32) * count, GL_DYNAMIC_DRAW);

	m_typeBuffer.SetVertecies(nullptr, sizeof(u8) * count, GL_DYNAMIC_DRAW);
	m_currentCount = count;
}

void PixelBody::Draw()
{
	if (m_pixelSoa.XPositions.size() < 1)
		return;

	if (!m_buffersUpToDate)
	{
		m_xBuffer.UpdateVertecies(m_pixelSoa.XPositions.data(), sizeof(i32) * m_pixelSoa.Count());
		m_yBuffer.UpdateVertecies(m_pixelSoa.YPositions.data(), sizeof(i32) * m_pixelSoa.Count());
		m_typeBuffer.UpdateVertecies(m_pixelSoa.Types.data(), sizeof(u8) * m_pixelSoa.Count());
		m_buffersUpToDate = true;
	}

	TransformComponent& t = *GetComponent<TransformComponent>();
	PixelCollisionComponent& pc = *GetComponent<PixelCollisionComponent>();

	m_shader.GlShader().Use();

	glm::mat4 m = t.ModelMatrix(z);
	m_shader.SetUniformMatrix4("model"_id, m);
	m_shader.SetUniformVec2("u_offset"_id, Vector2(-pc.GetCenterOfMass().x + 0.5, -pc.GetCenterOfMass().y + 0.5));

	m_vao.Bind();

	GL_CHECK(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_pixelSoa.Count()));
}

void PixelBody::SetPixel(i32 x, i32 y, u8 type)
{
	std::vector<size_t> xs;
	for (int i = 0; i < m_pixelSoa.Count(); i++)
	{
		if (m_pixelSoa.XPositions[i] == x)
			xs.push_back(i);
	}

	for (int i = 0; i < xs.size(); i++)
	{
		if (m_pixelSoa.YPositions[xs[i]] == y)
		{
			m_pixelSoa.Types[xs[i]] = type;
			m_buffersUpToDate = false;
			m_chunkState++;
			return;
		}
	}

	AddPixel(x, y, type);
}

void PixelBody::AddPixel(i32 x, i32 y, u8 type)
{
	m_pixelSoa.Add(x, y, type);
	m_buffersUpToDate = false;
	m_chunkState++;

	if (m_pixelSoa.Count() >= m_currentCount)
		ResizeBuffers(m_pixelSoa.Count() * 1.5f);

	PixelCollisionComponent& c = *GetComponent<PixelCollisionComponent>();

	c.PixelsChanged();
}