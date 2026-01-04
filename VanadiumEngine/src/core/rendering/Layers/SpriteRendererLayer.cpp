#include "pch.h"
#include "SpriteRendererLayer.h"
#include "Components.h"
#include "core/Rendering/GLCommon.h"
#include "core/Components/SpriteRendererComponent.h"
#include "Rendering.h"
#include "core/Rendering/Util.h"
#include "ECS.h"

namespace Vanadium
{
	using Vanadium::Application;
	using Vanadium::Detail::Rendering::RenderingManager;

	SpriteRendererLayer::SpriteRendererLayer()
		: m_textureShader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/texture.shader")->CreateShader().value()), m_VAO(Util::SquareVertexArray())
	{
		RenderingManager& man = *Application::Get().GetRenderingManager();
		UniformBindingVoucher bindingVoucher = man.ClaimBindingSlot();
		UniformObjectDescriptor matricesDescriptor = m_textureShader.Descriptor().FindUniformObjectDescriptor("Matrices");
		Handle<UniformObject> handle = man.CreateUniformObject(matricesDescriptor);
		UniformObject* object = man.GetUniformObject(handle);
		object->Bind(std::move(bindingVoucher));
		m_textureShader.TryUseUniformObject(*object, ShaderType::VertexShader);
	}

	void SpriteRendererLayer::OnUpdate(double dt)
	{

	}

	void SpriteRendererLayer::OnRender(double dt)
	{
		AssetManager* assetManager = Application::Get().GetAssetManager();
		EntityComponentSystem* ECS = Application::Get().GetECS();

		ComponentStore<SpriteRendererComponent>* spStore = ECS->GetComponentStore<SpriteRendererComponent>();
		ComponentStore<TransformComponent>* tStore = ECS->GetComponentStore<TransformComponent>();

		UnorderedVector<SpriteRendererComponent>& sps = spStore->GetComponents();
		unsigned int m_samplerId = m_textureShader.GlShader().GetUniformLocation("u_sampler");
		unsigned int m_modelMatrix = m_textureShader.GlShader().GetUniformLocation("u_model");

		RenderingManager& man = *Application::Get().GetRenderingManager();
		GL_CHECK(glActiveTexture(GL_TEXTURE0));
		GL_CHECK(glUniform1i(m_samplerId, 0));
		m_textureShader.GlShader().Use();
		m_VAO.Bind();

		for (int i = 0; i < sps.size(); i++)
		{
			TransformComponent& tc = *sps[i].GetEntity().GetComponent<TransformComponent>();

			GL_CHECK(glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(tc.ModelMatrix())));

			GLTexture& texture = GetTexture(sps[i].Texture);
			texture.Use();
			GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
		}
	}

	GLTexture& SpriteRendererLayer::GetTexture(std::shared_ptr<TextureRGBAAsset> texture)
	{
		if (m_readyTexture.contains(texture))
		{
			return m_readyTexture.at(texture);
		}

		m_readyTexture.try_emplace(texture);
		GLTexture& tex = m_readyTexture.at(texture);
		tex.AssignTexture(texture->Texture);

		return tex;
	}
}