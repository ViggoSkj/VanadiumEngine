#pragma once
#include "Includes/Core.h"

class GridBackgroundLayer : public ApplicationLayer
{
public:
	GridBackgroundLayer();

	void OnRender(double dt) override;

private:
	Shader m_shader;
	VertexArray m_vao;
};