#pragma once
#include "Primitives/VertexArray.h"
#include "Primitives/IndexBuffer.h"
#include "Primitives/VertexBuffer.h"

namespace Util
{
	inline VertexArray Square()
	{
		float vertices[] = {
			 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,  // top right
			 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bottom right
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  // bottom left
			-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,  // top left 
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
}