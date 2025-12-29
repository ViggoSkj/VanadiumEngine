#pragma once
#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/Rendering/GLCommon.h"
#include "core/InputManager/InputManager.h"

namespace Vanadium
{
	class Window
	{
	public:
		Window(int width, int height);
		Window(const Window&) = delete;
		~Window();

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		bool ShouldClose() const { return glfwWindowShouldClose(m_window.get()); }
		void SwapBuffers() const { glfwSwapBuffers(m_window.get()); }

		bool WindowSizeChanged();

		glm::mat4 GetOrthographicProjection();

		std::shared_ptr<GLFWwindow> GetGLFWwindow() { return m_window; }

		void ProcessInput();

		const InputManager& GetInputManager() const { return m_inputManager; };

	private:
		int m_width;
		int m_height;

		InputManager m_inputManager;

		std::shared_ptr<GLFWwindow> m_window;
	};
}