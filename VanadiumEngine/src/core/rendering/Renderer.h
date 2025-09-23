#pragma once
#include <memory>
#include <vector>
#include "VertexArray.h"
#include "Window.h"


class Renderer
{
public:
	Renderer(Window& window);
	~Renderer();

	Window& GetWindow() { return m_window; }

private:
	Window& m_window;
};