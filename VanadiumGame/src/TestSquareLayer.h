#pragma once
#include <optional>
#include "core/ApplicationLayer.h"
#include "core/Rendering/Rendering.h"
#include "core/Rendering/Shaders/UniformBufferManager.h"
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
	Shader m_shader;
	UniformObject m_matrices;
	VertexArray m_VAO;
	Camera m_camera;
	unsigned int m_samplerId;
	unsigned int m_timeId;
};

