#pragma once
#include "Core.h"
#include "SymbolSheet.h"
#include "SymbolRenderer.h"

class UiRenderingLayer : public ApplicationLayer
{
public:
	UiRenderingLayer();

	void OnRender(double dt) override;

private:
	Shader m_shader;
	RenderObject m_quad;
};