#pragma once
#include "Core.h"
#include "SymbolSheet.h"
#include "SymbolRenderer.h"
#include "Ui.h"
#include "UiTree.h"

class UiRenderingLayer : public ApplicationLayer
{
public:
	UiRenderingLayer();

	void OnUpdate(double dt) override;
	void OnRender(double dt) override;
	void OnEvent(Vanadium::Event& event) override;

	bool OnClick(Vanadium::MouseButtonDownEvent& event);

private:
	UiTree m_tree;
	std::vector<ClickableBox> m_clickableBoxes;

	Shader m_shader;
	RenderObject m_quad;
};