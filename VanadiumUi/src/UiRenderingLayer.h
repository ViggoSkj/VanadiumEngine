#pragma once
#include "Core.h"
#include "SymbolSheet.h"
#include "SymbolRenderer.h"

class UiRenderingLayer : public ApplicationLayer
{
public:
	UiRenderingLayer();

	void OnRender(double dt) override;
	void OnEvent(Vanadium::Event& event) override;

	bool OnClick(Vanadium::MouseButtonDownEvent& event);

private:
	Shader m_shader;
	RenderObject m_quad;
};