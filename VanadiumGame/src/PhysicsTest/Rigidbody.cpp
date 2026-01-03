#include "Rigidbody.h"
#include "Core.h"

Vector2 Rigidbody::GetPosition()
{
	TransformComponent& t = *GetEntity().GetComponent<TransformComponent>();
	return t.Position;
}

TransformComponent* Rigidbody::GetTransform()
{
	return GetEntity().GetComponent<TransformComponent>();
}
