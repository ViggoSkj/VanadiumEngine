#pragma once
#include "core/Rendering/Primitives/VertexBuffer.h"
#include "core/Rendering/Primitives/IndexBuffer.h"
#include "core/CoreTypes.h"

namespace Vanadium::Rendering
{
	struct Mesh
	{
		VertexBuffer vertices;
		IndexBuffer indices;
		i32 indexCount;
	};

	struct MeshHandle
	{
		u32 meshIndex;
		u32 generation;
	};
}