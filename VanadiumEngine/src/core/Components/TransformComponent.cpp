#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(unsigned int owner)
	: Component(owner)
{
	Position = { rand() % 4 - 2, rand() % 4 - 2 };
}
