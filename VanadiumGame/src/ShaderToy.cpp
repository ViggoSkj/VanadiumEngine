#include "ShaderToy.h"

void ShaderToySetup::Execute()
{
	EntityRef ref = CreateEntity();
	ref.Get().AddComponent<TransformComponent>();
	ref.Get().AddComponent<CameraComponent>();
	ref.Get().AddComponent<ShaderToy>();
}

ShaderToy::ShaderToy(EntityRef ref)
	: LiveComponent(ref),
	m_VAO(Util::Square()),
	m_shaderPath("res/shaders/shaderToy.shader"),
	m_shader(std::nullopt),
	m_fileWatcher(
		m_shaderPath,
		std::bind(&ShaderToy::OnFileChange, this)
	),
	m_needUpdate(std::make_shared<std::atomic<bool>>(false))
{
	UpdateShader();
}

void ShaderToy::UpdateShader()
{
	AssetManager& man = *Application::Get().GetAssetManager();
	man.FlushFileAsset<ShaderCodeAsset>(m_shaderPath);
	try {
		m_shader = man.GetFileAsset<ShaderCodeAsset>(m_shaderPath)->CreateShader();
		if (m_shader.has_value())
		{
			RenderingManager& renderingMan = *Application::Get().GetRenderingManager();
			UniformBindingSlot slot = renderingMan.LoanUniformBindingSlot(ShaderType::VertexShader);
			UniformObjectDescriptor matricesDescriptor = m_shader.value().Descriptor().FindUniformObjectDescriptor("Matrices");
			m_shader.value().ReportUniformObject(*renderingMan.FindUniformObject("Matrices").value());
		}
	}
	catch (int errorCode) {
		m_shader = std::nullopt;
		std::cout << "Error occurred: " << errorCode;
	}
}

void ShaderToy::OnRender(double dt)
{
	if (m_needUpdate->load())
	{
		UpdateShader();
		m_needUpdate->store(false);
	}

	if (m_shader.has_value())
	{
		m_VAO.Bind();
		m_shader.value().GlShader().Use();

		GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	}
}

void ShaderToy::OnFileChange()
{
	m_needUpdate->store(true);
}