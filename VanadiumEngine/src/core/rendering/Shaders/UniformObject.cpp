#include "pch.h"
#include "UniformObject.h"
#include "ShaderDataTypeMaps.h"

namespace Vanadium
{
	static i32 UniformVectorSize(std::vector<UniformDescriptor> vector)
	{
		i32 total = 0;
		for (i32 i = 0; i < vector.size(); i++)
		{
			total += ShaderDataTypeToSize.at(vector[i].type);
		}
		return total;
	}

	UniformObject::UniformObject(const UniformObjectDescriptor& descriptor)
		: Descriptor(descriptor), Buffer(UniformVectorSize(descriptor.Uniforms), GL_STREAM_DRAW)
	{
	}

	void UniformObject::Bind(UniformBindingVoucher bindingSlot)
	{
		Buffer.SetBindingPoint(bindingSlot.Slot());
		m_bindingSlot.emplace(std::move(bindingSlot));
	}
}