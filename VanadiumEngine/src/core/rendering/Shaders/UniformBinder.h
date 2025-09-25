#pragma once
#include <vector>
#include "AssetTypes/Shader/ShaderDescriptor.h"
#include "Shaders/UniformObject.h"
#include "Shaders/ShaderType.h"
#include "Shaders/UniformBindingSlot.h"

class UniformBinder
{
public:
	static unsigned int BlockCount(GLenum block);

	UniformBinder(ShaderType shaderType, unsigned int count);

	UniformBindingSlot LoneBindingSlot();
	void ReturnBindingSlot(UniformBindingSlot bindingSlot);

private:
	std::vector<UniformBindingSlot> m_bindingSlots;
};