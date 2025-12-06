#include "Rigidbody.h"
#include "Core.h"

Vector2 Rigidbody::GetPosition()
{
	TransformComponent& t = *GetComponent<TransformComponent>().value_or(nullptr);
	return t.Position;
}
