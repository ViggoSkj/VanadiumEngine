#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/Application.h"

struct Camera
{
	glm::vec2 Position = glm::vec2(0, 0);
	float Zoom = 1.0f;

	glm::mat4 GetViewMatrix()
	{
		glm::mat4 camera = glm::identity<glm::mat4>();
		camera = glm::scale(camera, glm::vec3(1.0 / Zoom, 1.0 / Zoom, 1.0f));
		camera = glm::translate(camera, glm::vec3(-Position.x, -Position.y, 0.0f));
		return camera;
	}
};