#include "pch.h"
#include "Window.h"
#include "Monitor/Monitor.h"
#include "core/InputManager/KeyMaps.h"

namespace Vanadium
{
	void glfw_window_deleter(GLFWwindow* window) {
		if (window) {
			glfwDestroyWindow(window);
		}
	}

	Window::Window(WindowOptions options)
	{
		m_width = options.width;
		m_height = options.height;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_width, m_height, "LearnOpenGL", NULL, NULL), glfw_window_deleter);

		if (m_window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		switch (options.placementType)
		{
		case WindowPlacementType::Absolute:
		{
			SetPosition(options.absolute);
			break;
		}
		case WindowPlacementType::Monitor:
		{
			SetPosition(options.monitor);
			break;
		}
		default:
			break;
		}

		glfwMakeContextCurrent(m_window.get());
	}

	Window::Window(int width, int height)
		: Window(WindowOptions(width, height, 0))
	{


	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::SetPosition(WindowMonitorPosition position)
	{
		std::span<GLFWmonitor*> monitors = Monitor::GetMonitors();

		GLFWmonitor* monitor;
		if (position.monitorIndex < monitors.size())
			monitor = monitors[position.monitorIndex];
		else
			monitor = monitors[0];

		RectI workingArea = Monitor::GetWorkingArea(monitor);
		Vector2I p = workingArea.start + (workingArea.end - workingArea.start - Vector2I(m_width, m_height)) / 2;
		SetPosition(p);
	}

	void Window::SetPosition(Vector2I position)
	{
		glfwSetWindowPos(m_window.get(), position.x, position.y);
	}

	bool Window::WindowSizeChanged()
	{
		int activeWidth = 0;
		int activeHeight = 0;

		glfwGetFramebufferSize(m_window.get(), &activeWidth, &activeHeight);

		if (m_width != activeWidth || m_height != activeHeight)
		{
			m_width = activeWidth;
			m_height = activeHeight;
			return true;
		}

		return false;
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
}