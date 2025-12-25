#include "Rigidbody.h"
#include "Core.h"

Vector2 Rigidbody::GetPosition()
{
	TransformComponent& t = *GetComponent<TransformComponent>();
	return t.Position;
}

TransformComponent* Rigidbody::GetTransform()
{
	return GetComponent<TransformComponent>();
}
