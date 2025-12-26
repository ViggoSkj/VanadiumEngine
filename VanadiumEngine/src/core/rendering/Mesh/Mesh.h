#pragma once
#include "core/Rendering/Primitives/VertexBuffer.h"
#include "core/Rendering/Primitives/IndexBuffer.h"
#include "core/CoreTypes.h"

namespace Vanadium::Rendering
{
	class MeshData
	{
	public:
		i32 AddVertex(Vector3 pos, Vector2 uv);
		void AddIndex(u32 vertex);

		size_t VertexCount() const { return m_vertices.size(); }
		float* Vertices() { return m_vertices.data(); };

		size_t IndexCount() const { return m_indices.size(); }
		u32* Indices() { return m_indices.data(); };
	private:
		std::vector<float> m_vertices;
		std::vector<u32> m_indices;
	};

	struct Mesh
	{
		Mesh(MeshData data);

		Mesh(Mesh&& other) noexcept;

		Mesh& operator=(Mesh&& other) noexcept
		{
			if (this == &other)
				return *this;

			this->indexBuffer = std::move(other.indexBuffer);
			this->vertexBuffer = std::move(other.vertexBuffer);
			this->indexCount = other.indexCount;

			return *this;
		}

		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		i32 indexCount;
	};

	struct MeshHandle
	{
		MeshHandle(u32 meshIndex, u32 generation);

		u32 meshIndex;
		u32 generation;
	};
}