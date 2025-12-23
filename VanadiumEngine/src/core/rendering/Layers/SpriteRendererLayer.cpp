#include "pch.h"
#include "SpriteRendererLayer.h"
#include "Components.h"
#include "GLCommon.h"
#include "core/Components/SpriteRendererComponent.h"
#include "Rendering.h"
#include "Util.h"
#include "ECS.h"

SpriteRendererLayer::SpriteRendererLayer()
	: m_textureShader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/texture.shader")->CreateShader().value()), m_VAO(Util::SquareVertexArray())
{
	RenderingManager& man = *Application::Get().GetRenderingManager();
	UniformBindingSlot slot = man.LoanUniformBindingSlot(ShaderType::VertexShader);
	UniformObjectDescriptor matricesDescriptor = m_textureShader.Descriptor().FindUniformObjectDescriptor("Matrices");
	UniformObject& m_matrices = *man.CreateUniformObject(matricesDescriptor);
	m_matrices.Bind(slot);
	m_textureShader.ReportUniformObject(m_matrices);
}

void SpriteRendererLayer::OnUpdate(double dt) 
{

}

void SpriteRendererLayer::OnRender(double dt)
{
	AssetManager* assetManager = Application::Get().GetAssetManager();
	EntityComponentSystem* ECS = Application::Get().GetECS();

	ComponentStore<SpriteRendererComponent>* spStore = ECS->GetComponentStore<SpriteRendererComponent>().value();
	ComponentStore<TransformComponent>* tStore = ECS->GetComponentStore<TransformComponent>().value();

	UnorderedVector<SpriteRendererComponent>& sps = spStore->GetComponents();

	unsigned int m_samplerId = m_textureShader.GlShader().GetUniformLocation("u_sampler");
	unsigned int m_modelMatrix = m_textureShader.GlShader().GetUniformLocation("u_model");

	glm::mat4 proj = Application::Get().GetWindow()->GetOrthographicProjection();

	std::optional<CameraComponent*> oCameraComponent = CameraComponent::GetMain();

	if (!oCameraComponent.has_value())
	{
		std::cout << "no main camera" << std::endl;
		return;
	}

	glm::mat4 view = oCameraComponent.value()->GetCamera().GetViewMatrix();

	RenderingManager& man = *Application::Get().GetRenderingManager();
	UniformObject& m_matrices = *man.FindUniformObject("Matrices").value();
	m_matrices.Buffer.SetData(glm::value_ptr(proj), 0, 4 * 4 * 4);
	m_matrices.Buffer.SetData(glm::value_ptr(view), 4 * 4 * 4, 4 * 4 * 4);

	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	GL_CHECK(glUniform1i(m_samplerId, 0));
	m_textureShader.GlShader().Use();
	m_VAO.Bind();

	for (int i = 0; i < sps.size(); i++)
	{
		Entity& e = *ECS->FindEntity(sps[i].GetOwnerId()).value();
		TransformComponent& tc = *e.GetComponent<TransformComponent>().value();

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
	tex.AssignTexture((Texture*) &texture->Texture);
	
	return tex;
}
