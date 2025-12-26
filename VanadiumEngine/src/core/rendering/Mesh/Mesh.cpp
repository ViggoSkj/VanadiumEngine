#include "pch.h"
#include "Mesh.h"

namespace Vanadium::Rendering
{
	i32 MeshData::AddVertex(Vector3 pos, Vector2 uv)
	{
		m_vertices.push_back(pos.x);
		m_vertices.push_back(pos.y);
		m_vertices.push_back(pos.z);
		m_vertices.push_back(uv.x);
		m_vertices.push_back(uv.y);

		return (m_vertices.size() / 5) - 1;
	}
	void MeshData::AddIndex(u32 vertexIndex)
	{
		m_indices.push_back(vertexIndex);
	}

	Mesh::Mesh(MeshData data)
		: indexCount(data.IndexCount())
	{
		vertexBuffer.SetVertecies(data.Vertices(), data.VertexCount() * sizeof(float), GL_STATIC_DRAW);
		indexBuffer.SetData(data.Indices(), data.IndexCount());
	}

	Mesh::Mesh(Mesh&& other) noexcept
		: vertexBuffer(std::move(other.vertexBuffer))
		, indexBuffer(std::move(other.indexBuffer))
		, indexCount(other.indexCount)
	{

	}

	MeshHandle::MeshHandle(u32 meshIndex, u32 generation)
		: meshIndex(meshIndex), generation(generation)
	{

	}
}
