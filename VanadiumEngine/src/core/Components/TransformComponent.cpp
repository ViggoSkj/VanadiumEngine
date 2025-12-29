#include "pch.h"
#include "TransformComponent.h"
#include "core/EntityComponentSystem/EntityRef.h"
#include <glm/gtc/matrix_transform.hpp>

TransformComponent::TransformComponent(EntityRef entityRef)
	: Component(entityRef)
{
}

Matrix4x4 TransformComponent::ModelMatrix()
{
	return ModelMatrix(0.5);
}

Matrix4x4 TransformComponent::ModelMatrix(float z)
{
	glm::mat4 model = glm::identity<glm::mat4>();
	model = glm::translate(model, glm::vec3(Position, z));
	model = glm::rotate(model, RotationAngle(), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(Scale, 1));
	return model;
}