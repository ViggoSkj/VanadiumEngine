#include "pch.h"
#include "TransformComponent.h"
#include "core/EntityComponentSystem/EntityRef.h"

TransformComponent::TransformComponent(EntityRef entityRef)
	: Component(entityRef), Position(glm::vec2(0, 0))
{
}
