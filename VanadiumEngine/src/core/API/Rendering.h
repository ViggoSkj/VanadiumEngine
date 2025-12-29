#pragma once
#include "core/Rendering/Mesh/MeshStore.h"	
#include "core/Rendering/Primitives/VertexArray.h"

namespace Vanadium::Rendering
{
	constexpr std::vector<GLVertexAttribute> MeshDataAttributes();

	MeshHandle CreateMesh(MeshData mesh);
	Mesh* GetMesh(MeshHandle handle);

	VertexArray CreateVertexArray(MeshHandle handle);
}