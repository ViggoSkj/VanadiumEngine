#include "ShaderToy.h"
#include "core/EntityComponentSystem/EntityRef.h"
#include "core/ShapeRenderer/ShapeRenderer.h"

using Vanadium::Detail::Rendering::RenderingManager;

void ShaderToySetup::Execute()
{
	EntityRef ref = CreateEntity();
	ref.Get().AddComponent<TransformComponent>();
	ref.Get().AddComponent<CameraComponent>()->Zoom = 3.0;
	ref.Get().AddComponent<ShaderToy>();

	EntityRef ref2 = CreateEntity();
	TransformComponent* t = ref2.Get().AddComponent<TransformComponent>();
	t->Position = Vector2(1.0, 0.0);
	t->Scale = Vector2(1.0, 2.0);
	ref2.Get().AddComponent<ShaderToy>();

	EntityRef ref3 = CreateEntity();
	TransformComponent* t2 = ref3.Get().AddComponent<TransformComponent>();
	t2->Position = Vector2(-1.0, 0.0);
	t2->Scale = Vector2(1.0, 0.5);
	ref3.Get().AddComponent<ShaderToy>();
}

ShaderToy::ShaderToy(EntityRef ref)
	: LiveComponent(ref),
	m_VAO(Util::SquareVertexArray()),
	m_shaderPath("res/shaders/shaderToy.shader"),
	m_shader(std::nullopt),
	m_fileWatcher(
		m_shaderPath,
		[entityId = ref.GetId()]()
		{
			Application::Get().GetECS()
				->FindEntity(entityId)
				->GetComponent<ShaderToy>()
				->OnFileChange();
		}
	),
	m_needUpdate(std::make_shared<std::atomic<bool>>(true))
{
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
	TransformComponent* t = GetComponent<TransformComponent>();

	ShapeRenderer::Get()->FillCircle(t->Position, t->Scale.y, { 0.0, 0.0, 0.0, 1.0 });

	return;

	if (m_needUpdate->load())
	{
		UpdateShader();
		m_needUpdate->store(false);
	}

	if (m_shader.has_value())
	{
		m_shader.value().GlShader().Use();

		int loc = m_shader.value().GlShader().GetUniformLocation("u_model");

		TransformComponent* t = GetComponent<TransformComponent>();

		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(t->ModelMatrix()));

		m_VAO.Bind();
		GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	}
}

void ShaderToy::OnFileChange()
{
	m_needUpdate->store(true);
}