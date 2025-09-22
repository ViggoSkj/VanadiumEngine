#include "TestSquareLayer.h"
#include "core/AssetManager/AssetTypes/Texture/TextureAsset.h"
#include "core/AssetManager/AssetTypes/Shader/ShaderSourceObject.h"

TestSquareLayer::TestSquareLayer()
{
	Application& application = Application::Get();
	AssetManager& assetManager = application.GetAssetManager();

	// texture
	AssetRef ref = assetManager.LoadFileAsset<TextureRGBAAsset>("res/images/player-running.png");
	TextureRGBA tex = assetManager.GetAsset<TextureRGBAAsset>(ref).Texture;
	m_texture.AssignTexture((Texture*) &tex);
	m_texture.Use();

	// shader
	AssetRef shaderRef = assetManager.LoadFileAsset<ShaderSourceObject>("res/shaders/texture.shader");
	ShaderSourceObject o = assetManager.GetAsset<ShaderSourceObject>(shaderRef);
	shader = Shader(o);
	m_samplerId = shader.GetUniformLocation("u_sampler");
	m_matrixUniforms.SetBindingPoint(0);
	

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
	glCheckError();
	glUniform1i(m_samplerId, 0);
	glCheckError();
	m_texture.Bind();
	m_VAO.Bind();
	shader.Use();

	glm::mat4 proj = app.GetWindow().GetOrthographicProjection();
	glm::mat4 view = m_camera.GetViewMatrix();

	m_matrixUniforms.SetData(glm::value_ptr(proj), 0, sizeof(float) * 4 * 4);
	m_matrixUniforms.SetData(glm::value_ptr(view), sizeof(float) * 4 * 4, sizeof(float) * 4 * 4);


	glCheckError();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
