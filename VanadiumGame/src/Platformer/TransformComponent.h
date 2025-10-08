#pragma once
#include "ECS.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>


class TransformComponent : public Component
{
public:
	TransformComponent(TransformComponent&& other) noexcept = default;
	TransformComponent& operator=(TransformComponent && other) noexcept = default;

	TransformComponent(unsigned int owner);


	glm::vec2 Position;

	glm::mat4 ModelMatrix()
	{
		return glm::translate(glm::identity<glm::mat4>(), glm::vec3(Position, 0.0));
	}
};