#pragma once
#include "Shaders/ShaderType.h"

struct UniformBindingSlot
{
	UniformBindingSlot(ShaderType shaderType, unsigned int slot)
		: ShaderType(shaderType), Slot(slot) {
	};

	unsigned int Slot;
	ShaderType ShaderType;
};