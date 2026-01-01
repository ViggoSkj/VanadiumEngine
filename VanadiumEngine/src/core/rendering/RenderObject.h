#pragma once
#include "core/Rendering/Primitives/VertexArray.h"
#include "core/Rendering/Mesh/Mesh.h"

namespace Vanadium
{
	using Vanadium::Rendering::Mesh;
	using Vanadium::Rendering::MeshHandle;

	class RenderObject
	{
	public:
		RenderObject(MeshHandle handle);

		void Render();
		bool IsValid() const { return m_valid; }

		VertexArray vertexArray;
		MeshHandle meshHandle;
	private:
		bool m_valid = false;
	};
}