#include "TestSquareLayer.h"
#include <iostream>
#include "core/AssetManager/AssetTypes/Texture/TextureAsset.h"
#include "core/rendering/RenderingManager.h"

TestSquareLayer::TestSquareLayer()
	: m_shader(Application::Get().GetAssetManager().LoadAndGetFileAsset<ShaderAsset>("res/shaders/texture.shader").ShaderProgram)
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

	// TODO FIGURE OUT HOW TO MANAGE THE BUFFERS BINDING POINTS


	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	m_VAO.Bind();

	VertexBuffer vertexBuffer;
	vertexBuffer.SetVertecies(vertices, sizeof(vertices));
	vertexBuffer.Bind();

	IndexBuffer indexBuffer;
	indexBuffer.SetData(indices, sizeof(indices));
	indexBuffer.Bind();

	m_VAO.AssignVertexAttributes({
		{sizeof(float), GL_FLOAT, 3},
		{sizeof(float), GL_FLOAT, 2},
		});
}

void TestSquareLayer::OnUpdate(double dt)
{
	GLFWwindow* glfwWindow = Application::Get().GetWindow().GetGLFWwindow().get();

	if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_camera.Position.y += 1.0f * (float)dt / m_camera.Zoom;
	}
	if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_camera.Position.y -= 1.0f * (float)dt / m_camera.Zoom;
	}
	if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_camera.Position.x -= 1.0f * (float)dt / m_camera.Zoom;
	}
	if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_camera.Position.x += 1.0f * (float)dt / m_camera.Zoom;
	}
	if (glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS)
	{
		m_camera.Zoom += 1.0f * (float)dt * m_camera.Zoom;
	}
	if (glfwGetKey(glfwWindow, GLFW_KEY_E) == GLFW_PRESS)
	{
		m_camera.Zoom -= 1.0f * (float)dt * m_camera.Zoom;
	}
}

void TestSquareLayer::OnRender(double dt)
{
	Application& app = Application::Get();

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_samplerId, 0);
	m_texture.Bind();
	m_VAO.Bind();
	m_shader.GlShader().Use();

	glm::mat4 proj = app.GetWindow().GetOrthographicProjection();
	glm::mat4 view = m_camera.GetViewMatrix();

	m_matrices.Buffer.SetData(glm::value_ptr(proj), 0, 4 * 4 * 4);
	m_matrices.Buffer.SetData(glm::value_ptr(view), 4 * 4 * 4, 4 * 4 * 4);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
