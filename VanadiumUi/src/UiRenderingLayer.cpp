#include "UiRenderingLayer.h"

UiRenderingLayer::UiRenderingLayer()
	: m_quad(Vanadium::Rendering::CreateMesh(Vanadium::Util::SquareMeshData(1.0)))
	, m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/box.shader")->CreateShader().value())
{
	Vanadium::RenderingManager& man = *Application::Get().GetRenderingManager();
	Vanadium::UniformObject* object = man.FindUniformObject("Matrices").value();
	m_shader.TryUseUniformObject(*object, Vanadium::ShaderType::VertexShader);
}

void UiRenderingLayer::OnRender(double dt)
{
	glm::mat4 proj = Application::Get().GetWindow()->GetOrthographicProjection();

	Vanadium::RenderingManager& man = *Application::Get().GetRenderingManager();
	Vanadium::UniformObject& m_matrices = *man.FindUniformObject("Matrices").value();
	m_matrices.Buffer.SetData(glm::value_ptr(proj), 0, 4 * 4 * 4);

	m_shader.Use();
	m_quad.Render();
}