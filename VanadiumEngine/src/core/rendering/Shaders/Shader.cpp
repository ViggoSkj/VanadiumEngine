#include "Shader.h"
#include "core/Processing/Shader/Tokenizer/ShaderTokenizer.h"
#include "core/Processing/Shader/CodeGenerator/ShaderCodeGenerator.h"

Shader::Shader(std::string source, ShaderDescriptor descriptor)
	: m_shaderDescriptor(descriptor)
{
	m_shaderProgram.LoadSource(source.c_str());
}


void Shader::ReportUniformObject(UniformObject object)
{
	std::optional<UniformBindingSlot> oslot = object.GetBindingSlot();

	if (!oslot.has_value())
		return;

	UniformBindingSlot slot = oslot.value();

	switch (slot.ShaderType)
	{
	case (ShaderType::VertexShader):
		if (!m_shaderDescriptor.VertexShader.UsesUniformObject(object.Descriptor.Name))
			return;
		break;
	default:
		return;
	}

	m_shaderProgram.ConfigureUniformBlock(object.Descriptor.Name.data(), slot.Slot);
}
