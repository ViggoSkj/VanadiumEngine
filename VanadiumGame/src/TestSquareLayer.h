#pragma once
#include "core/ApplicationLayer.h"
#include "core/rendering/Rendering.h"

class TestSquareLayer : public ApplicationLayer
{
public:
	TestSquareLayer();

	void OnRender(double dt) override;

private:
	GLTexture m_texture;
	VertexArray m_VAO;
	Shader shader;
	unsigned int m_samplerId;
};

