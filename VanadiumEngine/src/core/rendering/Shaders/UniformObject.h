#pragma once
#include <optional>
#include "Descriptors/ShaderDescriptor.h"
#include "GLUniformBuffer.h"
#include "UniformBindingSlot.h"

namespace Vanadium
{
	class UniformObject
	{
	public:
		UniformObject() = default;
		UniformObject(const UniformObjectDescriptor& descriptor);

		void Bind(UniformBindingSlot bindingSlot);

		const std::string_view GetName() const { return Descriptor.Name; };

		UniformObjectDescriptor Descriptor;
		GLUniformBuffer Buffer;

		std::optional<UniformBindingSlot> GetBindingSlot() const { return m_bindingSlot; };

	private:
		std::optional<UniformBindingSlot> m_bindingSlot;
	};
}