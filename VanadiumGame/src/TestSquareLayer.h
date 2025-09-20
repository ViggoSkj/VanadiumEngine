#pragma once
#include "core/ApplicationLayer.h"
#include "core/rendering/Rendering.h"

class TestSquareLayer : public ApplicationLayer
{
public:
	TestSquareLayer();

	void OnUpdate(double dt) override;
	void OnRender(double dt) override;

private:
	GLTexture m_texture;
	UniformBuffer m_matrixUniforms;
	VertexArray m_VAO;
	Shader shader;
	Camera m_camera;
	unsigned int m_samplerId;
};

