#pragma once
#include "Core.h"
#include "SymbolSheet.h"

class UiRenderingLayer : public ApplicationLayer
{
public:
	UiRenderingLayer();

	void OnRender(double dt) override;

private:
	Shader m_shader;
	RenderObject m_quad;
	SymbolSheet m_symbolSheet;
};