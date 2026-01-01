#pragma once
#include <optional>
#include "Descriptors/ShaderDescriptor.h"
#include "GLUniformBuffer.h"
#include "UniformBindingVoucher.h"

namespace Vanadium
{
	class UniformObject
	{
	public:
		UniformObject() = default;
		UniformObject(const UniformObjectDescriptor& descriptor);

		void Bind(UniformBindingVoucher bindingSlot);

		const std::string_view GetName() const { return Descriptor.Name; };

		i32 BindingSlot() const { return m_bindingSlot.has_value() ? m_bindingSlot.value().Slot() : -1; };

		UniformObjectDescriptor Descriptor;
		GLUniformBuffer Buffer;
	private:
		std::optional<UniformBindingVoucher> m_bindingSlot;
	};
}