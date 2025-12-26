#pragma once
#include "Primitives/VertexArray.h"
#include "Primitives/IndexBuffer.h"
#include "Primitives/VertexBuffer.h"

namespace Util
{
	std::array<float, 5 * 4> RectVertices(float width, float height, bool centered, bool uvs);
	
	VertexArray SquareVertexArray();
	VertexArray RectVertexArray(float width, float height);
}