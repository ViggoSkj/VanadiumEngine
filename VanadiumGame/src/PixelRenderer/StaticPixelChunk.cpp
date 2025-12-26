#include "StaticPixelChunk.h"
#include "PixelWorld.h"
#include "core/API/Rendering.h"
#include "core/Util/StringHash.h"

StaticPixelChunk::StaticPixelChunk(EntityRef ref)
	: Component(ref),
	m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/chunk.shader")->CreateShader().value()),
	Position(Vector2(0, 0))
{
	using namespace Vanadium::Rendering;

	m_vao = CreateVertexArray(CreateMesh(Util::SquareMeshData(PixelWorld::PixelSize)));

	m_vao.AddVertexBuffer({ GLVertexAttribute(GL_UNSIGNED_BYTE, 1, GL_TRUE) }, m_xBuffer, 1, 1);
	m_vao.AddVertexBuffer({ GLVertexAttribute(GL_UNSIGNED_BYTE, 1, GL_TRUE) }, m_yBuffer, 2, 1);
	m_vao.AddVertexBuffer({ GLVertexAttribute(GL_UNSIGNED_BYTE, 1, GL_TRUE) }, m_typeBuffer, 3, 1);

	m_xBuffer.SetVertecies(nullptr, Size * Size, GL_DYNAMIC_DRAW);
	m_yBuffer.SetVertecies(nullptr, Size * Size, GL_DYNAMIC_DRAW);
	m_typeBuffer.SetVertecies(nullptr, Size * Size, GL_DYNAMIC_DRAW);

	m_shader.SetUniformFloat("u_size"_id, PixelWorld::PixelSize);
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
	m_chunkState++;
}

void StaticPixelChunk::SetPixel(LocalChunkPosition position, u8 type)
{
	SetPixel(position.x, position.y, type);
}

void StaticPixelChunk::SetPixel(u8 x, u8 y, u8 type)
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

void StaticPixelChunk::RemovePixels(ChunkedPixelRefs& refs)
{
	for (int i = refs.Size() - 1; i >= 0; i--)
	{
		m_soa_x.remove(refs[i]);
		m_soa_y.remove(refs[i]);
		m_soa_type.remove(refs[i]);
	}

	m_chunkState++;
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
	GL_CHECK(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::identity<glm::mat4>(), glm::vec3(((Vector2)Position) * ChunkSize, 0.0)))));

	m_shader.GlShader().Use();
	m_vao.Bind();

	GL_CHECK(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_soa_x.size()));
}

ChunkedPixelRefs StaticPixelChunk::RectCast(Rect cast)
{
	std::vector<size_t> pixels;
	for (int i = 0; i < m_soa_x.size(); i++)
	{
		float x = ChunkSize * (m_soa_x[i] + 0.5) / ((float)Size) + ((float)Position.x) * ChunkSize;
		if (x >= cast.Start.x && x <= cast.End.x)
			pixels.push_back(i);
	}

	for (int i = 0; i < pixels.size(); i++)
	{
		float y = ChunkSize * (m_soa_y[pixels[i]] + 0.5) / ((float)Size) + ((float)Position.y) * ChunkSize;
		if (y < cast.Start.y || y > cast.End.y)
		{
			pixels.erase(pixels.begin() + i);
			i--;
		}
	}

	return ChunkedPixelRefs(std::move(pixels), this);
}

Rect StaticPixelChunk::GetRect()
{
	return Rect(((Vector2)Position) * ChunkSize, ((Vector2)Position) * ChunkSize + Vector2(ChunkSize, ChunkSize));
}
