#pragma once
#include "core/ApplicationLayer.h"
#include "core/rendering/Rendering.h"
#include "core/rendering/Shaders/UniformBufferManager.h"
#include "core/Shaders.h"

class TestSquareLayer : public ApplicationLayer
{
public:
	TestSquareLayer();

	void OnUpdate(double dt) override;
	void OnRender(double dt) override;

private:
	GLTexture m_texture;
	UniformBufferManager m_uniformBufferManager;
	GLShader m_shader;
	VertexArray m_VAO;
	Camera m_camera;
	unsigned int m_samplerId;
};

