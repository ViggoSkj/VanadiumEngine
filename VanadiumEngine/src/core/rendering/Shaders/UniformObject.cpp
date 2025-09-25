#include "UniformObject.h"
#include "AssetTypes/Shader/ShaderDataTypeMaps.h"

static unsigned int UniformVectorSize(std::vector<UniformDescriptor> vector)
{
	unsigned int total = 0;
	for (int i = 0; i < vector.size(); i++)
	{
		total += ShaderDataTypeToSize.at(vector[i].type);
	}
	return total;
}

UniformObject::UniformObject(const UniformObjectDescriptor& descriptor)
	: Descriptor(descriptor), Buffer(UniformVectorSize(descriptor.Uniforms), GL_STREAM_DRAW)
{
}

void UniformObject::Bind(UniformBindingSlot bindingSlot)
{
	Buffer.SetBindingPoint(bindingSlot);
	m_bindingSlot.emplace(bindingSlot);
}

