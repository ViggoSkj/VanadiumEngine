#include "SpriteRendererLayer.h"
#include "GLCommon.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Util.h"
#include "Entity.h"

SpriteRendererLayer::SpriteRendererLayer()
	: m_textureShader(Application::Get().GetAssetManager().LoadAndGetFileAsset<ShaderAsset>("res/shaders/texture.shader").ShaderProgram), m_VAO(Util::Square())
{
	RenderingManager man;

	AssetManager assetManager = Application::Get().GetAssetManager();

	UniformBindingSlot slot = man.LoanUniformBindingSlot(ShaderType::VertexShader);
	UniformObjectDescriptor matricesDescriptor = m_textureShader.Descriptor().FindUniformObjectDescriptor("Matrices");
	m_matrices = UniformObject(matricesDescriptor);
	m_matrices.Bind(slot);

	m_textureShader.ReportUniformObject(m_matrices);


	Entity e1;
	ComponentRef ref = e1.AddComponent<SpriteRendererComponent>();
	e1.GetComponent<SpriteRendererComponent>(ref).TextureRef = assetManager.LoadFileAsset<TextureRGBAAsset>("res/images/player-running.png");
}

void SpriteRendererLayer::OnRender(double dt)
{
	Application& app = Application::Get();
	AssetManager assetManager = app.GetAssetManager();

	ComponentStore<SpriteRendererComponent>* spStore = Entity::GetComponentStore<SpriteRendererComponent>();
	ComponentStore<TransformComponent>* tStore = Entity::GetComponentStore<TransformComponent>();

	UnorderedVector<SpriteRendererComponent>& sps = spStore->GetComponents();

	Camera camera;

	unsigned int m_samplerId = m_textureShader.GlShader().GetUniformLocation("u_sampler");
	unsigned int m_modelMatrix = m_textureShader.GlShader().GetUniformLocation("u_sampler");

	glm::mat4 proj = app.GetWindow().GetOrthographicProjection();
	glm::mat4 view = camera.GetViewMatrix();

	m_matrices.Buffer.SetData(glm::value_ptr(proj), 0, 4 * 4 * 4);
	m_matrices.Buffer.SetData(glm::value_ptr(view), 4 * 4 * 4, 4 * 4 * 4);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_samplerId, 0);
	m_textureShader.GlShader().Use();
	m_VAO.Bind();

	for (int i = 0; i < sps.Size(); i++)
	{
		sps
		GLTexture& texture = GetTexture(sps.Get(i).TextureRef);
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
