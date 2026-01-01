#include "UiRenderingLayer.h"

UiRenderingLayer::UiRenderingLayer()
	: m_quad(Vanadium::Rendering::CreateMesh(Vanadium::Util::SquareMeshData(1.0)))
	, m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/box.shader")->CreateShader().value())
{
	Vanadium::RenderingManager& man = *Application::Get().GetRenderingManager();
	Vanadium::UniformBindingSlot slot = man.LoanUniformBindingSlot(Vanadium::ShaderType::VertexShader);
	Vanadium::UniformObjectDescriptor matricesDescriptor = m_shader.Descriptor().FindUniformObjectDescriptor("Matrices");
	Vanadium::UniformObject& m_matrices = *man.CreateUniformObject(matricesDescriptor);
	m_matrices.Bind(slot);
	m_shader.ReportUniformObject(m_matrices);
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