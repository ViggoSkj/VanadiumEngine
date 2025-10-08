#include "Shader.h"
#include "core/Processing/Shader/Tokenizer/ShaderTokenizer.h"
#include <optional>

Shader::Shader(std::string source)
	: m_shaderDescriptor(Tokenizer::Tokenize(source))
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
