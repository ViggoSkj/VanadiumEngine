#include "pch.h"
#include "Window.h"
#include "core/InputManager/KeyMaps.h"

void glfw_window_deleter(GLFWwindow* window) {
	if (window) {
		glfwDestroyWindow(window);
	}
}

Window::Window(int width, int height)
{
	m_width = width;	
	m_height = height;	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_width, m_height, "LearnOpenGL", NULL, NULL), glfw_window_deleter);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window.get());
}

Window::~Window()
{
	glfwTerminate();
}

glm::mat4 Window::GetOrthographicProjection()
{
	float sw = (float)m_width / (float)m_height;
	float sh = 1.0;

	float left = -sw / 2.0f;
	float right = sw / 2.0f;
	float bottom = -sh / 2.0f;
	float top = sh / 2.0f;

	return glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

void Window::ProcessInput()
{
	bool states[Key::_LAST];

	for (int i = 0; i < Key::_LAST; i++)
	{
		int glfwKey = GlfwKeyMappings[i];
		states[i] = glfwGetKey(m_window.get(), glfwKey) == GLFW_PRESS;
	}

	m_inputManager.ReportNewKeyStates(states);
}