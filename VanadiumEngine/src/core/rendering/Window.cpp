#include "Window.h"

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
