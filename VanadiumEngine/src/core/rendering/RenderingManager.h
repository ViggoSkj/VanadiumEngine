#pragma once
#include <memory>

#include "Shaders/ShaderUniform.h"
#include "Shaders/ShaderType.h"
#include "Shaders/UniformBinder.h"
#include "Shaders/UniformBindingSlot.h"
#include "Shaders/Shader.h"
#include "core/Util/UnorderdVector.h"

class RenderingManager
{
public:
	RenderingManager();
	RenderingManager(const RenderingManager&) = delete;

	UniformBindingSlot LoanUniformBindingSlot(ShaderType shaderType);
	void ReturnuniformBindingSlot(UniformBindingSlot bindingSlot);

	UniformObject* CreateUniformObject(UniformObjectDescriptor descriptor);
	std::optional<UniformObject*> FindUniformObject(std::string name);

private:
	UniformBinder m_vertexUniformBinder;
	std::vector<UniformObject> m_uniformObjects;
};