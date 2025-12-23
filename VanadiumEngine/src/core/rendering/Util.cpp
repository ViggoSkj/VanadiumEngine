#include "pch.h"
#include "Util.h"

float* RectVerticesNoUvs(float width, float height, bool centered)
{
	if (centered)
	{
		return new float[4 * 5] {
			width / 2.0f, height / 2.0f, 1.0f,  // top right
				width / 2.0f, -height / 2.0f, 1.0f, // bottom right
				-width / 2.0f, -height / 2.0f, 1.0f,  // bottom left
				-width / 2.0f, height / 2.0f, 1.0f, // top left
			};
	}


	return new float[4 * 5] {
		width, height, 1.0f,  // top right
			width, 0.0f, 1.0f, // bottom right
			0.0f, 0.0f, 1.0f,   // bottom left
			0.0f, height, 1.0f,  // top left 
		};
}

float* RectVerticesUvs(float width, float height, bool centered)
{
	if (centered)
	{
		return new float[4 * 5] {
			width / 2.0f, height / 2.0f, 1.0f, 1.0f, 0.0f,  // top right
				width / 2.0f, -height / 2.0f, 1.0f, 1.0f, 1.0f,  // bottom right
				-width / 2.0f, -height / 2.0f, 1.0f, 0.0f, 1.0f,  // bottom left
				-width / 2.0f, height / 2.0f, 1.0f, 0.0f, 0.0f,  // top left
			};
	}


	return new float[4 * 5] {
		width, height, 1.0f, 1.0f, 0.0f,  // top right
			width, 0.0f, 1.0f, 1.0f, 1.0f,  // bottom right
			0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // bottom left
			0.0f, height, 1.0f, 0.0f, 0.0f,  // top left 
		};
}

float* Util::RectVertices(float width, float height, bool centered, bool uvs)
{
	if (uvs)
		return RectVerticesUvs(width, height, centered);
	else
		return RectVerticesNoUvs(width, height, centered);
}

VertexArray Util::SquareVertexArray()
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

VertexArray Util::RectVertexArray(float width, float height)
{
	float* vertices = Util::RectVertices(width, height, true, true);

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