#include "UiRenderingLayer.h"

UiRenderingLayer::UiRenderingLayer()
	: m_quad(Vanadium::Rendering::CreateMesh(Vanadium::Util::SquareMeshData(1.0)))
	, m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/box.shader")->CreateShader().value())
{
}

void UiRenderingLayer::OnRender(double dt)
{
	m_shader.Use();
	m_quad.Render();
}