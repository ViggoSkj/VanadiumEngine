#include "PixelBody.h"
#include "StaticPixelChunk.h"

PixelBody::PixelBody(EntityRef ref)
	: Component(ref),
	m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/chunk.shader")->CreateShader())
{
	UpdateMesh();
}

void PixelBody::UpdateMesh()
{
	float pixelSize = StaticPixelChunk::ChunkSize / (float)(StaticPixelChunk::Size - 1);
	float* vertices = Util::RectVertices(pixelSize, pixelSize);

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

	m_xBuffer.SetVertecies(nullptr, sizeof(u8) * m_currentCount, GL_DYNAMIC_DRAW);
	m_xBuffer.Bind();
	m_vao.AssignVertexAttributes({
		{sizeof(u8), GL_UNSIGNED_BYTE, 1},
		}, 1, GL_TRUE);

	m_yBuffer.SetVertecies(nullptr, sizeof(u8) * m_currentCount, GL_DYNAMIC_DRAW);
	m_yBuffer.Bind();
	m_vao.AssignVertexAttributes({
		{sizeof(u8), GL_UNSIGNED_BYTE, 1},
		}, 1, GL_TRUE);

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
	m_xBuffer.SetVertecies(nullptr, sizeof(u8) * count, GL_DYNAMIC_DRAW);
	m_xBuffer.Bind();

	m_yBuffer.SetVertecies(nullptr, sizeof(u8) * count, GL_DYNAMIC_DRAW);
	m_yBuffer.Bind();

	m_typeBuffer.SetVertecies(nullptr, sizeof(u8) * count, GL_DYNAMIC_DRAW);
	m_typeBuffer.Bind();
	m_currentCount = count;
}

void PixelBody::Draw()
{
	if (m_soa_x.size() < 1)
		return;

	if (!m_buffersUpToDate)
	{
		m_xBuffer.UpdateVertecies(m_soa_x.data(), sizeof(u8) * m_soa_x.size());
		m_yBuffer.UpdateVertecies(m_soa_y.data(), sizeof(u8) * m_soa_y.size());
		m_typeBuffer.UpdateVertecies(m_soa_type.data(), sizeof(u8) * m_soa_type.size());
		m_buffersUpToDate = true;
	}

	TransformComponent& t = *GetComponent<TransformComponent>().value_or(nullptr);

	m_shader.GlShader().Use();
	u32 loc = m_shader.GlShader().GetUniformLocation("model");
	glm::mat4 m = t.ModelMatrix();
	GL_CHECK(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m)));

	m_vao.Bind();

	GL_CHECK(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_soa_x.size()));
}

void PixelBody::SetPixel(u8 x, u8 y, u8 type)
{
	std::vector<size_t> xs;
	for (int i = 0; i < m_soa_x.size(); i++)
	{
		if (m_soa_x[i] == x)
			xs.push_back(i);
	}

	for (int i = 0; i < xs.size(); i++)
	{
		if (m_soa_y[xs[i]] == y)
		{
			m_soa_type[xs[i]] = type;
			m_buffersUpToDate = false;
			m_chunkState++;
			return;
		}
	}

	AddPixel(x, y, type);
}

void PixelBody::AddPixel(u8 x, u8 y, u8 type)
{
	m_soa_x.push_back(x);
	m_soa_y.push_back(y);
	m_soa_type.push_back(type);
	m_buffersUpToDate = false;
	m_chunkState++;

	if (m_soa_x.size() >= m_currentCount)
	{
		ResizeBuffers(m_soa_x.size() * 1.5f);
	}
}