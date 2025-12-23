#pragma once
#include "pch.h"
#include "core/EntityComponentSystem/Component.h"

# define M_PI           3.14159265358979323846  /* pi */

#define DEG_TO_RAD M_PI/180.0f

class TransformComponent : public Component
{
public:
	TransformComponent(TransformComponent&& other) noexcept = default;
	TransformComponent& operator=(TransformComponent&& other) noexcept = default;

	TransformComponent(EntityRef entityRef);

	Vector2 Position = Vector2(0.0, 0.0);
	Vector2 Scale = Vector2(1.0, 1.0);

	float Angle = 0.0f;
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
		Angle = deg * DEG_TO_RAD;
		Up.x = sin(deg * Angle);
		Up.y = cos(deg * Angle);
	}

	void RotateRads(float rads)
	{
		Angle += rads;
		Up.x = sin(Angle);
		Up.y = cos(Angle);
	}

	Matrix4x4 ModelMatrix();
};