#pragma once
#include "Primitives/VertexArray.h"
#include "Primitives/IndexBuffer.h"
#include "Primitives/VertexBuffer.h"
#include "Mesh/Mesh.h"

namespace Vanadium::Util
{
	using Vanadium::Rendering::MeshData;

	MeshData SquareMeshData(float width);
	VertexArray SquareVertexArray();
}