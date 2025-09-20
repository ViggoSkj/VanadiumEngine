#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/Application.h"

struct Camera
{
	glm::vec2 Position;
	float Zoom;

	glm::mat4 GetOrthographicProjection()
	{
		Window& window = Application::Get().GetWindow();

		int width = window.GetWidth();
		int height = window.GetHeight();

		float sw = (float)width / (float)height;
		float sh = 1.0;

		float left = -sw / 2.0f;
		float right = sw / 2.0f;
		float bottom = -sh / 2.0f;
		float top = sh / 2.0f;

		glm::mat4 projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		glm::mat4 camera = glm::identity<glm::mat4>();
		camera = glm::scale(camera, glm::vec3(Zoom, Zoom, 1.0f));
		camera = glm::translate(camera, glm::vec3(-Position.x, -Position.y, 0.0f));

		return projection * camera;
	}
};