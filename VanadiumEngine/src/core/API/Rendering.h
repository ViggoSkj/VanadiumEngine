#pragma once
#include "Mesh/MeshStore.h"	
#include "Primitives/VertexArray.h"

namespace Vanadium::Rendering
{
	constexpr std::vector<GLVertexAttribute> MeshDataAttributes();

	MeshHandle CreateMesh(MeshData mesh);
	Mesh* GetMesh(MeshHandle handle);

	VertexArray CreateVertexArray(MeshHandle handle);
}