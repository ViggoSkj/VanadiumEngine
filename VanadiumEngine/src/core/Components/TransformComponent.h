#pragma once
#include "pch.h"
#include "core/EntityComponentSystem/Component.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

# define M_PI           3.14159265358979323846  /* pi */

#define DEG_TO_RAD M_PI/180.0f

class TransformComponent : public Component
{
public:
	TransformComponent(TransformComponent&& other) noexcept = default;
	TransformComponent& operator=(TransformComponent&& other) noexcept = default;

	TransformComponent(EntityRef entityRef);

	Vector2 Position = glm::vec2(0, 0);

	Vector2 Up = Vector2(1, 0);

	Vector2 Right()
	{
		return { Up.y, -Up.x };
	}

	float RotationAngle()
	{
		return std::atan2(Up.y, Up.x);
	}

	void SetAngleDeg(float deg)
	{
		Up.x = sin(deg * DEG_TO_RAD);
		Up.y = cos(deg * DEG_TO_RAD);
	}

	Matrix4x4 ModelMatrix()
	{
		glm::mat4 model = glm::identity<glm::mat4>();
		model = glm::translate(model, glm::vec3(Position, 0.0));
		model = glm::rotate(model, RotationAngle(), glm::vec3(0, 0, 1));
		return model;
	}
};