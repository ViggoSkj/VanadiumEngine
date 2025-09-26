#pragma once
#include <optional>
#include "Input.h"
#include "Application.h"
#include "Rendering.h"

class TestSquareLayer : public ApplicationLayer
{
public:
	TestSquareLayer();

	void OnUpdate(double dt) override;
	void OnRender(double dt) override;

private:
	GLTexture m_texture;
	Shader m_shader;
	UniformObject m_matrices;
	VertexArray m_VAO;
	Camera m_camera;
	unsigned int m_samplerId;
	unsigned int m_timeId;
};

