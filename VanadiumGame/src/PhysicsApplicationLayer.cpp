#include "PhysicsApplicationLayer.h"
#include "core/rendering/IndexBuffer.h"
#include "core/rendering/VertexBuffer.h"
#include "core/rendering/Renderer.h"

PhysicsApplicationLayer::PhysicsApplicationLayer()
{
	Renderer& renderer = Application::Get().GetRenderer();
	m_camera.Zoom = 0.1f;

	m_renderQueueItem = renderer.CreateRenderQueueItem();
	Shader& m_ballShader = m_renderQueueItem->shader;
	VertexArray& vertexArray = m_renderQueueItem->vertexArray;

	float vertices[] = {
	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  // top right
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	vertexArray.Bind();

	VertexBuffer vertexBuffer;
	vertexBuffer.SetVertecies(vertices, sizeof(vertices));
	vertexBuffer.Bind();

	IndexBuffer indexBuffer;
	indexBuffer.SetData(indices, sizeof(indices) / sizeof(unsigned int));
	indexBuffer.Bind();

	vertexArray.AssignVertexAttributes({
		{sizeof(float), GL_FLOAT, 3},
		{sizeof(float), GL_FLOAT, 2},
		});

	vertexArray.Bind();
	vertexBuffer.UnBind();

	m_instanceVertexBuffer.SetVertecies(m_simulation.GetTransforms().get(), Simulation::BallCount * 16 * sizeof(float), GL_STREAM_DRAW);
	m_instanceVertexBuffer.Bind();

	vertexArray.AssignVertexAttributes({
	{sizeof(float), GL_FLOAT, 4},
	{sizeof(float), GL_FLOAT, 4},
	{sizeof(float), GL_FLOAT, 4},
	{sizeof(float), GL_FLOAT, 4},
		}, 1);

	m_instanceVertexBuffer.UnBind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	m_ballShader.LoadSource("res/shaders/basic.shader");
	m_ballShader.Use();
	m_projectionMatrixUniformId = m_ballShader.GetUniformLocation("u_mvp");

	m_renderQueueItem->instanceCount = Simulation::BallCount;
	m_renderQueueItem->indexCount = 6;
}

PhysicsApplicationLayer::~PhysicsApplicationLayer()
{
}

void PhysicsApplicationLayer::OnUpdate(double dt)
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

	if (glfwGetKey(glfwWindow, GLFW_KEY_R) == GLFW_PRESS)
	{
		m_simulation.Reset();
	}

	m_simulation.PhysicsUpdate((float)dt);
}

void PhysicsApplicationLayer::OnRender(double dt)
{
	m_renderQueueItem->shader.Use();
	glm::mat4 projectionMatrix = m_camera.GetOrthographicProjection();
	glUniformMatrix4fv(m_projectionMatrixUniformId, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	m_instanceVertexBuffer.UpdateVertecies(m_simulation.GetTransforms().get(), Simulation::BallCount * 16 * sizeof(float), 0);

}
