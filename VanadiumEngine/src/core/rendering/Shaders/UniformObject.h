#pragma once
#include <optional>
#include "AssetTypes/Shader/ShaderDescriptor.h"
#include "Shaders/GLUniformBuffer.h"
#include "Shaders/UniformBindingSlot.h"

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