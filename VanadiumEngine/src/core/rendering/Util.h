#pragma once
#include "Primitives/VertexArray.h"
#include "Primitives/IndexBuffer.h"
#include "Primitives/VertexBuffer.h"

namespace Util
{
	float* RectVertices(float width, float height, bool centered, bool uvs);

	inline VertexArray Square()
	{
		float* vertices = Util::RectVertices(1, 1, true, true);

		unsigned int indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		VertexArray VAO;
		VAO.Bind();

		VertexBuffer vertexBuffer;
		vertexBuffer.SetVertecies(vertices, sizeof(float) * 4 * 5);
		vertexBuffer.Bind();

		IndexBuffer indexBuffer;
		indexBuffer.SetData(indices, sizeof(indices));
		indexBuffer.Bind();

		VAO.AssignVertexAttributes({
			{sizeof(float), GL_FLOAT, 3},
			{sizeof(float), GL_FLOAT, 2},
			});

		return VAO;
	}
}