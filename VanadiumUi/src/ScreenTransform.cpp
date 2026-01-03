#include "ScreenTransform.h"

Matrix4 ScreenTransform::ModelMatrix()
{
	glm::mat4 model = glm::identity<glm::mat4>();
	Vector2 size = Surface.Size();
	model = glm::translate(model, glm::vec3(Surface.Start, 0));
	model = glm::scale(model, glm::vec3(size, 1));
	return model;
}