#pragma once
#include "pch.h"
#include "core/EntityComponentSystem/Component.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>


class TransformComponent : public Component
{
public:
	TransformComponent(TransformComponent&& other) noexcept = default;
	TransformComponent& operator=(TransformComponent&& other) noexcept = default;

	TransformComponent(EntityRef entityRef);

	Vector2 Position;

	Matrix4x4 ModelMatrix()
	{
		return glm::translate(glm::identity<glm::mat4>(), glm::vec3(Position, 0.0));
	}
};