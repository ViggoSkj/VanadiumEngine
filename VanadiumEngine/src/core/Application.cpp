#include "pch.h"
#include <thread>
#include <chrono>
#include <memory>
#include <ranges>
#include "Application.h"
#include "core/Rendering/GLCommon.h"
#include "core/Debug/Log.h"
#include "core/ShapeRenderer/ShapeRendererLayer.h"

namespace Vanadium
{
	Application* Application::s_instance = nullptr;

	Application::Application(WindowOptions windowOptions)
		: m_eventQueue(std::make_shared<EventQueue>())
	{
		Application::s_instance = this;

		windowOptions.eventQueue = m_eventQueue;

		m_window = std::make_unique<Window>(windowOptions);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}


		m_time = std::make_unique<Time>();
		m_logger = std::make_unique<Logger>();
		m_ecs = std::make_unique<EntityComponentSystem>();
		m_assetManager = std::make_unique<AssetManager>();
		m_renderingManager = std::make_unique<RenderingManager>();
		m_sceneManager = std::make_unique<SceneManager>();

		GL_CHECK(glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight()));

		GL_CHECK(glEnable(GL_DEPTH_TEST));

		GL_CHECK(glDepthFunc(GL_LESS));

		GL_CHECK(glEnable(GL_MULTISAMPLE));
		
		GL_CHECK(glEnable(GL_BLEND));

		GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
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

			while (!m_eventQueue->Empty())
			{
				Event* event = m_eventQueue->PopEvent();
				for (auto& layer : std::views::reverse(m_applicationLayers))
				{
					layer->OnEvent(*event);
					if (event->Handled)
						break;
				}
			}

			m_eventQueue->Flush();

			if (!paused)
			{
				GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
				GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


				// Awake components

				m_ecs->AwakeComponents();

				// Run layers

				for (int i = 0; i < m_applicationLayers.size(); i++)
				{
					m_applicationLayers[i]->OnUpdate(dt);
				}

				m_renderingManager->UpdateRenderSurfaceUBO();
				m_renderingManager->UpdateCameraUBO();

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

	void Application::RaiseEvent(Event& event)
	{

	}
}