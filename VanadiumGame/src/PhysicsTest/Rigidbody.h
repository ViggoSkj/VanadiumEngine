#pragma once
#include "Core.h"

class Rigidbody : public Component
{
public:
	virtual Vector2 GetPosition();
	virtual TransformComponent* GetTransform();
	float InverseInertia;
	float InverseMass;
	Vector2 LinearVelocity = { 0, 0 };
	float AngularVelocity = 0;
};