#include "StaticPixelChunk.h"

StaticPixelChunk::StaticPixelChunk(EntityRef ref)
	: Component(ref), m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/chunk.shader")->CreateShader())
{

	float chunkSize = 1.0;

	float vertices[] = {
	chunkSize / (float)(Size - 1),  chunkSize / (float)(Size - 1), 0.0f, 1.0f, 0.0f,  // top right
	chunkSize / (float)(Size - 1),   0.0f, 0.0f, 1.0f, 1.0f,  // bottom right
	  0.0f,   0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
	  0.0f,  chunkSize / (float)(Size - 1), 0.0f, 0.0f, 0.0f,  // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	u32 loc = m_shader.GlShader().GetUniformLocation("u_size");
	GL_CHECK(glUniform1f(loc, chunkSize - 1/(float)(Size)));

	m_vao.Bind();

	VertexBuffer vertexBuffer;
	vertexBuffer.SetVertecies(vertices, sizeof(vertices));
	vertexBuffer.Bind();

	IndexBuffer indexBuffer;
	indexBuffer.SetData(indices, sizeof(indices));
	indexBuffer.Bind();

	m_vao.AssignVertexAttributes({
		{sizeof(float), GL_FLOAT, 3},
		{sizeof(float), GL_FLOAT, 2},
		});


	m_xBuffer.SetVertecies(nullptr, sizeof(u8) * Size * Size, GL_DYNAMIC_DRAW);
	m_xBuffer.Bind();
	m_vao.AssignVertexAttributes({
		{sizeof(u8), GL_UNSIGNED_BYTE, 1},
		}, 1, GL_TRUE);

	m_yBuffer.SetVertecies(nullptr, sizeof(u8) * Size * Size, GL_DYNAMIC_DRAW);
	m_yBuffer.Bind();
	m_vao.AssignVertexAttributes({
		{sizeof(u8), GL_UNSIGNED_BYTE, 1},
		}, 1, GL_TRUE);

	m_typeBuffer.SetVertecies(nullptr, sizeof(u8) * Size * Size, GL_DYNAMIC_DRAW);
	m_typeBuffer.Bind();
	m_vao.AssignVertexAttributes({
		{sizeof(u8), GL_UNSIGNED_BYTE, 1},
		}, 1, GL_TRUE);

}

void StaticPixelChunk::AddPixel(LocalChunkPosition position, u8 type)
{
	AddPixel(position.x, position.y, type);
}

void StaticPixelChunk::AddPixel(u8 x, u8 y, u8 type)
{
	m_soa_x.push_back(x);
	m_soa_y.push_back(y);
	m_soa_type.push_back(type);
	m_buffersUpToDate = false;
}

void StaticPixelChunk::Draw()
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

	u32 loc = m_shader.GlShader().GetUniformLocation("model");
	GL_CHECK(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::identity<glm::mat4>(), glm::vec3(Position, 0.0)))));

	m_shader.GlShader().Use();
	m_vao.Bind();

	GL_CHECK(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_soa_x.size()));
}
