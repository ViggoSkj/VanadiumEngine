#pragma once
#include <memory>
#include <vector>
#include "VertexArray.h"
#include "Shader.h"
#include "Window.h"

struct RenderQueueItem
{
	VertexArray vertexArray;
	Shader shader;
	unsigned int instanceCount;
	unsigned int indexCount;
};

class Renderer
{
public:
	Renderer(Window& window);
	~Renderer();

	RenderQueueItem* CreateRenderQueueItem();

	void Render();

	Window& GetWindow() { return m_window; }

private:
	Window& m_window;
	std::vector<RenderQueueItem> m_renderQueue;
};