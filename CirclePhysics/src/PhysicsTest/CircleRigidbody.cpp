#include "CircleRigidbody.h"
#include "Core.h"

Vector2 CircleRigidbody::GetPosition()
{
	TransformComponent& t = *GetComponent<TransformComponent>().value_or(nullptr);
	return t.Position;
}
