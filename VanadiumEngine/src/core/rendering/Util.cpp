#include "pch.h"
#include "Util.h"

float* RectVerticesNoUvs(float width, float height, bool centered)
{
	if (centered)
	{
		return new float[4 * 5] {
			width / 2.0f, height / 2.0f, 0.0f,  // top right
				width / 2.0f, -height / 2.0f, 0.0f, // bottom right
				-width / 2.0f, -height / 2.0f, 0.0f,  // bottom left
				-width / 2.0f, height / 2.0f, 0.0f, // top left
			};
	}


	return new float[4 * 5] {
		width, height, 0.0f,  // top right
			width, 0.0f, 0.0f, // bottom right
			0.0f, 0.0f, 0.0f,   // bottom left
			0.0f, height, 0.0f,  // top left 
		};
}

float* RectVerticesUvs(float width, float height, bool centered)
{
	if (centered)
	{
		return new float[4 * 5] {
			width / 2.0f, height / 2.0f, 0.0f, 1.0f, 0.0f,  // top right
				width / 2.0f, -height / 2.0f, 0.0f, 1.0f, 1.0f,  // bottom right
				-width / 2.0f, -height / 2.0f, 0.0f, 0.0f, 1.0f,  // bottom left
				-width / 2.0f, height / 2.0f, 0.0f, 0.0f, 0.0f,  // top left
			};
	}


	return new float[4 * 5] {
		width, height, 0.0f, 1.0f, 0.0f,  // top right
			width, 0.0f, 0.0f, 1.0f, 1.0f,  // bottom right
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
			0.0f, height, 0.0f, 0.0f, 0.0f,  // top left 
		};
}

float* Util::RectVertices(float width, float height, bool centered, bool uvs)
{
	if (uvs)
		return RectVerticesUvs(width, height, centered);
	else
		return RectVerticesNoUvs(width, height, centered);
}
