#include "ShaderToy.h"
#include "core/EntityComponentSystem/EntityRef.h"
#include "core/ShapeRenderer/ShapeRenderer.h"

void ShaderToySetup::Execute()
{
	EntityRef ref = CreateEntity();
	ref.Get().AddComponent<TransformComponent>();
	ref.Get().AddComponent<CameraComponent>()->Zoom = 3.0;
	ref.Get().AddComponent<ShaderToy>()->Length = 1.0;
	ref.Get().GetComponent<ShaderToy>().value()->Thickness = 1.0 / 25.0f;

	EntityRef e2 = CreateEntity();
	e2.Get().AddComponent<TransformComponent>()->Scale = Vector2(1.0 / 24.0f, 1.0);
	e2.Get().AddComponent<RectCollisionComponent>();

	EntityRef ref2 = CreateEntity();
	TransformComponent* t = ref2.Get().AddComponent<TransformComponent>();
	t->Position = Vector2(1.0, 0.0);
	t->Scale = Vector2(1.0, 2.0);
	ref2.Get().AddComponent<ShaderToy>()->Length = 2.0;
	ref2.Get().GetComponent<ShaderToy>().value()->Thickness = 1.0 / 25.0f;

	EntityRef ref3 = CreateEntity();
	TransformComponent* t2 = ref3.Get().AddComponent<TransformComponent>();
	t2->Position = Vector2(-1.0, 0.0);
	t2->Scale = Vector2(1.0, 0.5);
	ref3.Get().AddComponent<ShaderToy>()->Length = 0.5;
	ref3.Get().GetComponent<ShaderToy>().value()->Thickness = 1.0 / 25.0f;
}

ShaderToy::ShaderToy(EntityRef ref)
	: LiveComponent(ref),
	m_VAO(Util::RectVertexArray(0.1, 1.0)),
	m_shaderPath("res/shaders/shaderToy.shader"),
	m_shader(std::nullopt),
	m_fileWatcher(
		m_shaderPath,
		[entityId = ref.GetId()]()
		{
			Application::Get().GetECS()
				->FindEntity(entityId).value()
				->GetComponent<ShaderToy>().value()
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
	TransformComponent* t = GetComponent<TransformComponent>().value_or(nullptr);


	Vector2 Start = t->Position + Math::RotatePoint(Vector2(0, Length * cos(Application::Get().GetTime().TimeSinceStart)), Application::Get().GetTime().TimeSinceStart);
	Vector2 End = t->Position;

	ShapeRenderer::Get()->DrawArrow(Start, End, { 0.0, 0.0, 0.0, 0.0 });
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

		TransformComponent* t = GetComponent<TransformComponent>().value_or(nullptr);

		int loc2 = m_shader.value().GlShader().GetUniformLocation("u_length");
		if (loc2 >= 0)
			glUniform1f(loc2, Length);

		/*
		int loc3 = m_shader.value().GlShader().GetUniformLocation("u_thickness");
		if (loc3 >= 0)
			glUniform1f(loc3, Thickness * 2 + Thickness * std::sin(Application::Get().GetTime().TimeSinceStart));
		*/

		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(t->ModelMatrix()));

		m_VAO.Bind();
		GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	}
}

void ShaderToy::OnFileChange()
{
	m_needUpdate->store(true);
}