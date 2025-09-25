#pragma once
#include <memory>
#include <vector>
#include "Shaders/ShaderUniform.h"
#include "Shaders/ShaderType.h"
#include "Shaders/UniformBinder.h"
#include "Shaders/UniformBindingSlot.h"
#include "Shaders/Shader.h"
#include "core/util/UnorderdVector.h"

class RenderingManager
{
public:
	RenderingManager();

	UniformBindingSlot LoanUniformBindingSlot(ShaderType shaderType);
	void ReturnuniformBindingSlot(UniformBindingSlot bindingSlot);

private:
	UniformBinder m_vertexUniformBinder;

	std::vector<UniformObject> m_uniformObjects;
};