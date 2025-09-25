#pragma once
#include <optional>
#include "Descriptors/ShaderDescriptor.h"
#include "GLUniformBuffer.h"
#include "UniformBindingSlot.h"

class UniformObject
{
public:
	UniformObject() = default;
	UniformObject(const UniformObjectDescriptor& descriptor);

	void Bind(UniformBindingSlot bindingSlot);

	UniformObjectDescriptor Descriptor;
	GLUniformBuffer Buffer;

	std::optional<UniformBindingSlot> GetBindingSlot() const { return m_bindingSlot; };

private:
	std::optional<UniformBindingSlot> m_bindingSlot;
};