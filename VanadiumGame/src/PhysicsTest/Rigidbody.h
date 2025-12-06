#pragma once
#include "Core.h"

class Rigidbody : public Component
{
public:
	Vector2 GetPosition();
	float GetInertia()
	{
		RectCollisionComponent* collider = GetComponent<RectCollisionComponent>().value_or(nullptr);
		if (collider)
		{
			float width2 = collider->Rect.Width2();
			float height2 = collider->Rect.Height2();
			return (1.0f / 12.0f) * Mass * (width2 + height2);
		}
		return 0.0f;
	}


	Vector2 LinearVelocity;
	float Mass = 1;
	float AngularVelocity = 0;
};