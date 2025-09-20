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

	glViewport(0, 0, m_window.GetWidth(), m_window.GetHeight());
}

Renderer::~Renderer()
{

}

RenderQueueItem* Renderer::CreateRenderQueueItem()
{
	m_renderQueue.emplace_back();
	return &m_renderQueue.back();
}

void Renderer::Render()
{


	// -- RENDER LOGIC -- //

	for (int i = 0; i < m_renderQueue.size(); i++)
	{
		RenderQueueItem& item = m_renderQueue[i];
		item.shader.Use();
		item.vertexArray.Bind();
		glDrawElementsInstanced(GL_TRIANGLES, item.indexCount, GL_UNSIGNED_INT, 0, item.instanceCount);

	}

}
