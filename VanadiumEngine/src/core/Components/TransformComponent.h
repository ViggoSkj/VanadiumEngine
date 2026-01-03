#pragma once
#include "pch.h"
#include "core/Math.h"
#include "core/EntityComponentSystem/Component.h"

namespace Vanadium
{
	class TransformComponent : public Component
	{
	public:
		using Component::Component;

		Vector2 Position = Vector2(0.0, 0.0);
		Vector2 Scale = Vector2(1.0, 1.0);

		float Angle = 0.0f;
		Vector2 Up = Vector2(1, 0);

		Vector2 Right() const { return { Up.y, -Up.x }; }

		void SetAngleDeg(float deg);
		void RotateRads(float rads);

		Matrix4 ModelMatrix();
		Matrix4 ModelMatrix(float z);
	};
}