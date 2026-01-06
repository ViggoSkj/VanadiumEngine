#pragma once
#include <iostream>
#include <memory>
#include "core/Rendering/GLCommon.h"
#include "core/InputManager/InputManager.h"
#include "WindowOptions.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Vanadium
{
	class Window
	{
	public:
		Window(int width, int height);
		Window(WindowOptions options);
		Window(const Window&) = delete;
		~Window();

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		bool ShouldClose() const { return glfwWindowShouldClose(m_window); }
		void SwapBuffers() const { glfwSwapBuffers(m_window); }

		void SetPosition(WindowMonitorPosition position);
		void SetPosition(Vector2I position);

		bool WindowSizeChanged();

		glm::mat4 GetOrthographicProjection();

		void ProcessInput();

		const InputManager& GetInputManager() const { return m_inputManager; };

	private:
		void DispatchEvent(Event& event);

		int m_width;
		int m_height;

		std::function<void(Event& event)> m_eventCallback;
		InputManager m_inputManager;

		GLFWwindow* m_window;
	};
}