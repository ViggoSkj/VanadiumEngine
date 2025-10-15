#include "pch.h"
#include <thread>
#include <chrono>
#include "Application.h"
#include "GLCommon.h"
#include <memory>

Application* Application::s_instance = nullptr;

Application::Application()
	: Application(1600, 1000) {};

Application::Application(unsigned int width, unsigned int height)
{
	
	m_window = std::make_unique<Window>(width, height);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	m_sceneManager = std::make_unique<SceneManager>();
	m_renderingManager = std::make_unique<RenderingManager>();
	m_assetManager = std::make_unique<AssetManager>();
	m_ecs = std::make_unique<EntityComponentSystem>();
	m_time = std::make_unique<Time>();

	GL_CHECK(glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight()));

	GL_CHECK(glEnable(GL_BLEND));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Application::s_instance = this;
}

Application::~Application()
{
}

void Application::Run()
{
	float prevTime = (float)glfwGetTime();
	double fpsCap = 120;
	double minDt = 1.0 / fpsCap;
	while (m_running)
	{
		double dt = (double)glfwGetTime() - prevTime;

		if (dt < minDt)
		{
			std::this_thread::sleep_for(std::chrono::microseconds((long long)((minDt - dt) * 1000000)));
			dt = (double)glfwGetTime() - prevTime;
		}

		m_time->TimeSinceStart += dt;
		prevTime = (float)glfwGetTime();


		GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		m_window->ProcessInput();

		if (m_window->ShouldClose())
		{
			m_running = false;
			continue;
		}

		for (int i = 0; i < m_applicationLayers.size(); i++)
		{
			m_applicationLayers[i]->OnUpdate(dt);
		}

		for (int i = 0; i < m_applicationLayers.size(); i++)
		{
			m_applicationLayers[i]->OnRender(dt);
		}

		m_sceneManager->FlushCommands();
		m_window->SwapBuffers();
		glfwPollEvents();
	}
}

void Application::Stop()
{
	m_running = false;
}
