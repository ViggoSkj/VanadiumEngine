#include "Renderer.h"
#include "core/rendering/GLCommon.h"


Renderer::Renderer(Window& window)
	: m_window(window)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	GL_CHECK(glViewport(0, 0, m_window.GetWidth(), m_window.GetHeight()));
}

Renderer::~Renderer()
{

}