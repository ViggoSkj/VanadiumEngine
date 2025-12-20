#pragma once
#include "Core.h"

class Rigidbody : public Component
{
public:
	Rigidbody(EntityRef entityRef)
		: Component(entityRef)
	{
		InverseMass = 1.0f;
		InverseInertia = 1.0f;
	}

	Vector2 GetPosition();
	TransformComponent* GetTransform();
	float InverseInertia;
	float InverseMass;
	Vector2 LinearVelocity = { 0, 0 };
	float AngularVelocity = 0;
};