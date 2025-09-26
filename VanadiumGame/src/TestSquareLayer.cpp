#include "TestSquareLayer.h"
#include <iostream>
#include "core/AssetManager/AssetTypes/Texture/TextureAsset.h"
#include "core/Rendering/RenderingManager.h"
#include "Util.h"

TestSquareLayer::TestSquareLayer()
	: m_shader(Application::Get().GetAssetManager().LoadAndGetFileAsset<ShaderAsset>("res/shaders/texture.shader").ShaderProgram), m_VAO(Util::Square())
{
	RenderingManager man;

	Application& application = Application::Get();
	AssetManager& assetManager = application.GetAssetManager();

	// texture
	AssetRef ref = assetManager.LoadFileAsset<TextureRGBAAsset>("res/images/player-running.png");
	TextureRGBA tex = assetManager.GetAsset<TextureRGBAAsset>(ref).Texture;
	m_texture.AssignTexture((Texture*)&tex);
	m_texture.Use();

	// shader

	UniformBindingSlot slot = man.LoanUniformBindingSlot(ShaderType::VertexShader);

	UniformObjectDescriptor matricesDescriptor = m_shader.Descriptor().FindUniformObjectDescriptor("Matrices");
	m_matrices = UniformObject(matricesDescriptor);
	m_matrices.Bind(slot);
	m_shader.ReportUniformObject(m_matrices);

	m_samplerId = m_shader.GlShader().GetUniformLocation("u_sampler");
	m_timeId = m_shader.GlShader().GetUniformLocation("u_time");
}

void TestSquareLayer::OnUpdate(double dt)
{
	GLFWwindow* glfwWindow = Application::Get().GetWindow().GetGLFWwindow().get();

	InputManager man = Application::Get().GetWindow().GetInputManager();

	if (man.Down(Key::W))
	{
		m_camera.Position.y += 1.0f * (float)dt / m_camera.Zoom;
	}
	if (man.Down(Key::S))
	{
		m_camera.Position.y -= 1.0f * (float)dt / m_camera.Zoom;
	}
	if (man.Down(Key::A))
	{
		m_camera.Position.x -= 1.0f * (float)dt / m_camera.Zoom;
	}
	if (man.Down(Key::D))
	{
		m_camera.Position.x += 1.0f * (float)dt / m_camera.Zoom;
	}
	if (man.Down(Key::Q))
	{
		m_camera.Zoom += 1.0f * (float)dt * m_camera.Zoom;
	}
	if (man.Down(Key::E))
	{
		m_camera.Zoom -= 1.0f * (float)dt * m_camera.Zoom;
	}
}

void TestSquareLayer::OnRender(double dt)
{
	Application& app = Application::Get();

	m_shader.GlShader().Use();
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_samplerId, 0);
	glUniform1f(m_timeId, app.GetTime().TimeSinceStart);
	m_texture.Bind();
	m_VAO.Bind();

	glm::mat4 proj = app.GetWindow().GetOrthographicProjection();
	glm::mat4 view = m_camera.GetViewMatrix();

	m_matrices.Buffer.SetData(glm::value_ptr(proj), 0, 4 * 4 * 4);
	m_matrices.Buffer.SetData(glm::value_ptr(view), 4 * 4 * 4, 4 * 4 * 4);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
