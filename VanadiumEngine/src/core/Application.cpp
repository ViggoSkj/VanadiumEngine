#include "Application.h"
#include <memory>

Application* Application::s_instance = nullptr;

Application::Application()
	: m_window(1600, 1200), m_renderer(m_window)
{
	Application::s_instance = this;
}

Application::~Application()
{
}

void Application::Run()
{
	float prevTime = (float)glfwGetTime();

	while (m_running)
	{
		double dt = (double)glfwGetTime() - prevTime;
		prevTime = (float)glfwGetTime();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (m_window.ShouldClose())
		{
			m_running = false;
			continue;
		}

		for (int i = 0; i < m_applicationLayers.size(); i++)
		{
			m_applicationLayers[i]->OnUpdate(dt);
		}

		// m_renderer.Render();

		for (int i = 0; i < m_applicationLayers.size(); i++)
		{
			m_applicationLayers[i]->OnRender(dt);
		}

		m_window.SwapBuffers();
		glfwPollEvents();
	}
}

void Application::Stop()
{
	m_running = false;
}
