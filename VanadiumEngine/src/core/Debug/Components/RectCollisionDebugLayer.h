#pragma once
#include "core/ApplicationLayer.h"
#include "Core.h"

class RectCollisionDebugLayer : public ApplicationLayer
{
public:
	RectCollisionDebugLayer();

	void OnRender(double dt) override;

private:
	Shader shader;
	VertexArray vao;
};