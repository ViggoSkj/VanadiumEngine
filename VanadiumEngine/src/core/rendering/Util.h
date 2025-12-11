#pragma once
#include "Primitives/VertexArray.h"
#include "Primitives/IndexBuffer.h"
#include "Primitives/VertexBuffer.h"

namespace Util
{
	inline VertexArray Square()
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // top left 
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		VertexArray VAO;
		VAO.Bind();

		VertexBuffer vertexBuffer;
		vertexBuffer.SetVertecies(vertices, sizeof(vertices));
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

	inline float* RectVertices(float width, float height) // with uv
	{
		return new float[4 * 5] {
			width, height, 0.0f, 1.0f, 0.0f,  // top right
			width, 0.0f,   0.0f, 1.0f, 1.0f,  // bottom right
			0.0f,  0.0f,   0.0f, 0.0f, 1.0f,  // bottom left
			0.0f,  height, 0.0f, 0.0f, 0.0f,  // top left 
		};
	}
}