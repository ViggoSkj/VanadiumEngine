#include "SpriteRendererLayer.h"
#include "GLCommon.h"
#include "SpriteRendererComponent.h"
#include "Rendering.h"
#include "TransformComponent.h"
#include "Util.h"
#include "Components/Camera.h"	
#include "ECS.h"

SpriteRendererLayer::SpriteRendererLayer()
	: m_textureShader(Application::Get().GetAssetManager().LoadAndGetFileAsset<ShaderAsset>("res/shaders/texture.shader").ShaderProgram), m_VAO(Util::Square())
{
	RenderingManager man;
	AssetManager assetManager = Application::Get().GetAssetManager();
	EntityComponentSystem& ECS = Application::Get().GetECS();

	UniformBindingSlot slot = man.LoanUniformBindingSlot(ShaderType::VertexShader);
	UniformObjectDescriptor matricesDescriptor = m_textureShader.Descriptor().FindUniformObjectDescriptor("Matrices");
	m_matrices = UniformObject(matricesDescriptor);
	m_matrices.Bind(slot);

	Entity::GetComponentStore<MovableCameraComponent>()->CreateInstance(0);

	m_textureShader.ReportUniformObject(m_matrices);

	AssetRef texRef = assetManager.LoadFileAsset<TextureRGBAAsset>("res/images/player-running.png");
	AssetRef texRef2 = assetManager.LoadFileAsset<TextureRGBAAsset>("res/images/character.png");

	Entity& e1 = ECS.CreateEntity();
	ComponentRef ref = e1.AddComponent<SpriteRendererComponent>();
	e1.AddComponent<TransformComponent>();
	e1.GetComponent<SpriteRendererComponent>(ref).TextureRef = texRef;

	Entity& e2 = ECS.CreateEntity();
	ComponentRef ref2 = e2.AddComponent<SpriteRendererComponent>();
	e2.AddComponent<TransformComponent>();
	e2.GetComponent<SpriteRendererComponent>(ref).TextureRef = texRef2;
}

void SpriteRendererLayer::OnUpdate(double dt)
{

}

void SpriteRendererLayer::OnRender(double dt)
{
	Application& app = Application::Get();
	AssetManager assetManager = app.GetAssetManager();
	EntityComponentSystem& ECS = Application::Get().GetECS();

	ComponentStore<SpriteRendererComponent>* spStore = Entity::GetComponentStore<SpriteRendererComponent>();
	ComponentStore<TransformComponent>* tStore = Entity::GetComponentStore<TransformComponent>();

	UnorderedVector<SpriteRendererComponent>& sps = spStore->GetComponents();

	unsigned int m_samplerId = m_textureShader.GlShader().GetUniformLocation("u_sampler");
	unsigned int m_modelMatrix = m_textureShader.GlShader().GetUniformLocation("u_model");

	glm::mat4 proj = app.GetWindow().GetOrthographicProjection();
	glm::mat4 view = MovableCameraComponent::Main->Camera.GetViewMatrix();

	m_matrices.Buffer.SetData(glm::value_ptr(proj), 0, 4 * 4 * 4);
	m_matrices.Buffer.SetData(glm::value_ptr(view), 4 * 4 * 4, 4 * 4 * 4);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_samplerId, 0);
	m_textureShader.GlShader().Use();
	m_VAO.Bind();

	for (int i = 0; i < sps.size(); i++)
	{
		Entity& e = ECS.FindEntity(sps[i].GetOwnerId());
		TransformComponent& tc = e.GetComponent<TransformComponent>();

		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(tc.ModelMatrix()));

		GLTexture& texture = GetTexture(sps[i].TextureRef);
		texture.Use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

GLTexture& SpriteRendererLayer::GetTexture(AssetRef textureRef)
{
	AssetManager assetManager = Application::Get().GetAssetManager();

	if (m_readyTexture.contains(textureRef))
	{
		return m_readyTexture.at(textureRef);
	}

	TextureRGBAAsset& asset = assetManager.GetAsset<TextureRGBAAsset>(textureRef);

	m_readyTexture.try_emplace(textureRef);
	GLTexture& tex = m_readyTexture.at(textureRef);
	tex.AssignTexture((Texture*) &asset.Texture);
	
	return tex;
}
