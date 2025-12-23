#pragma once
#include "Primitives/VertexArray.h"
#include "Primitives/IndexBuffer.h"
#include "Primitives/VertexBuffer.h"

namespace Util
{
	float* RectVertices(float width, float height, bool centered, bool uvs);
	
	VertexArray SquareVertexArray();
	VertexArray RectVertexArray(float width, float height);
}