#pragma once

#include "Descriptors/ShaderDescriptor.h"
#include "UniformObject.h"
#include "ShaderType.h"
#include "UniformBindingSlot.h"

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