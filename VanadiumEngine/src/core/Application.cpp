#include "pch.h"
#include <thread>
#include <chrono>
#include "Application.h"
#include "GLCommon.h"
#include <memory>
#include "core/Debug/Log.h"
#include "core/ShapeRenderer/ShapeRendererLayer.h"

namespace Vanadium
{
	Application* Application::s_instance = nullptr;

	Application::Application()
		: Application(1600, 1000) {
	};

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
		m_logger = std::make_unique<Logger>();

		GL_CHECK(glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight()));

		GL_CHECK(glEnable(GL_BLEND));

		GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Application::s_instance = this;
	}

	Application::~Application()
	{
		m_applicationLayers.clear();
	}

	void Application::Run()
	{
		float prevTime = (float)glfwGetTime();
		double fpsCap = 1000;
		double minDt = 1.0 / fpsCap;
		while (m_running)
		{
			double dt = (double)glfwGetTime() - prevTime;

			if (dt < minDt)
			{
				std::this_thread::sleep_for(std::chrono::microseconds((long long)((minDt - dt) * 1000000)));
				dt = (double)glfwGetTime() - prevTime;
			}

			// LogDebug(std::to_string(1.0 / dt));

			m_time->TimeSinceStart += dt;
			prevTime = (float)glfwGetTime();

			m_window->ProcessInput();

			if (m_window->ShouldClose())
			{
				m_running = false;
				continue;
			}

			bool paused = false;
			if (m_window->GetInputManager().GetKey(Key::F1) == KeyState::Pressed)
				m_steppingMode = !m_steppingMode;

			if (m_steppingMode)
			{
				if (m_stepBuffered)
				{
					dt = m_stepDt;
					m_stepBuffered = false;
					paused = false;
				}
				else
				{
					if (m_window->GetInputManager().GetKey(Key::F2) == KeyState::Pressed)
						m_stepBuffered = true;

					dt = 1.0f / 60.0f;
					paused = true;
				}
			}

			if (!paused)
			{
				GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
				GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

				for (int i = 0; i < m_applicationLayers.size(); i++)
				{
					m_applicationLayers[i]->OnUpdate(dt);
				}

				for (int i = 0; i < m_applicationLayers.size(); i++)
				{
					m_applicationLayers[i]->OnRender(dt);
				}

				m_window->SwapBuffers();
			}


			if (m_window->WindowSizeChanged())
			{
				GL_CHECK(glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight()));
			}

			m_sceneManager->FlushCommands();
			m_ecs->Flush();
			glfwPollEvents();
		}
	}

	void Application::Stop()
	{
		m_running = false;
	}

	void Application::PushDefaultPostLayers()
	{
	}
}