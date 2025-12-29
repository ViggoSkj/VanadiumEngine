#pragma once
#include "core/Rendering/Shaders/ShaderType.h"

namespace Vanadium
{
	struct UniformBindingSlot
	{
		UniformBindingSlot(ShaderType shaderType, unsigned int slot)
			: ShaderType(shaderType), Slot(slot) {
		};

		unsigned int Slot;
		ShaderType ShaderType;
	};
}