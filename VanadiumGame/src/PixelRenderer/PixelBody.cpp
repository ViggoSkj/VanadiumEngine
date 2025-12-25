#include "PixelBody.h"
#include "StaticPixelChunk.h"
#include "PixelCollisionComponent.h"
#include "PixelWorld.h"
#include "core/Util/StringHash.h"

PixelBody::PixelBody(EntityRef ref)
	: Component(ref),
	m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/pixelbody.shader")->CreateShader().value()),
	m_pixelSoa()
{
	UpdateMesh();
}

void PixelBody::UpdateMesh()
{
	float pixelSize = PixelWorld::PixelSize;
	float* vertices = Util::RectVertices(pixelSize, pixelSize, true, true);

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	m_currentCount = 1000;

	m_vao.Bind();

	VertexBuffer vertexBuffer;
	vertexBuffer.SetVertecies(vertices, sizeof(float) * 5 * 4);
	vertexBuffer.Bind();

	IndexBuffer indexBuffer;
	indexBuffer.SetData(indices, sizeof(indices));
	indexBuffer.Bind();

	m_vao.AssignVertexAttributes({
		{sizeof(float), GL_FLOAT, 3},
		{sizeof(float), GL_FLOAT, 2},
		});

	m_xBuffer.SetVertecies(nullptr, sizeof(i32) * m_currentCount, GL_DYNAMIC_DRAW);
	m_xBuffer.Bind();
	m_vao.AssignVertexAttributes({
		{sizeof(i32), GL_INT, 1},
		}, 1, GL_FALSE);

	m_yBuffer.SetVertecies(nullptr, sizeof(i32) * m_currentCount, GL_DYNAMIC_DRAW);
	m_yBuffer.Bind();
	m_vao.AssignVertexAttributes({
		{sizeof(i32), GL_INT, 1},
		}, 1, GL_FALSE);

	m_typeBuffer.SetVertecies(nullptr, sizeof(u8) * m_currentCount, GL_DYNAMIC_DRAW);
	m_typeBuffer.Bind();
	m_vao.AssignVertexAttributes({
		{sizeof(u8), GL_UNSIGNED_BYTE, 1},
		}, 1, GL_TRUE);

	m_shader.GlShader().Use();
	u32 loc = m_shader.GlShader().GetUniformLocation("u_size");
	GL_CHECK(glUniform1f(loc, pixelSize));
}

void PixelBody::ResizeBuffers(u32 count)
{
	m_xBuffer.SetVertecies(nullptr, sizeof(i32) * count, GL_DYNAMIC_DRAW);
	m_xBuffer.Bind();

	m_yBuffer.SetVertecies(nullptr, sizeof(i32) * count, GL_DYNAMIC_DRAW);
	m_yBuffer.Bind();

	m_typeBuffer.SetVertecies(nullptr, sizeof(u8) * count, GL_DYNAMIC_DRAW);
	m_typeBuffer.Bind();
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

	TransformComponent& t = *GetComponent<TransformComponent>().value_or(nullptr);
	PixelCollisionComponent& pc = *GetComponent<PixelCollisionComponent>().value_or(nullptr);

	m_shader.GlShader().Use();

	glm::mat4 m = t.ModelMatrix();
	m_shader.SetUniformMatrix4("model"_id, m);

	i32 loc = m_shader.GlShader().GetUniformLocation("u_offset");
	GL_CHECK(glUniform2f(loc, -pc.GetCenterOfMass().x + 0.5, -pc.GetCenterOfMass().y +0.5));

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
	{
		ResizeBuffers(m_pixelSoa.Count() * 1.5f);
	}

	PixelCollisionComponent& c = *GetComponent<PixelCollisionComponent>().value();

	c.PixelsChanged();
}