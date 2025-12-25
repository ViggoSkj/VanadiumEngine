#include "pch.h"
#include "Shader.h"
#include "core/Processing/Shader/Tokenizer/ShaderTokenizer.h"
#include "core/Processing/Shader/CodeGenerator/ShaderCodeGenerator.h"
#include "core/Util/StringHash.h"
#include "core/Debug/Log.h"
#include "glm/gtc/type_ptr.hpp"


std::optional<Shader> Shader::CreateShader(std::string source, ShaderDescriptor descriptor)
{
	Shader shader(source, descriptor);
	if (!shader.GlShader().Ready())
		return std::nullopt;

	return shader;
}

Shader::Shader(std::string source, ShaderDescriptor descriptor)
	: m_shaderDescriptor(descriptor)
{
	m_shaderProgram.LoadSource(source.c_str());

	// shader compilation failed.
	if (!m_shaderProgram.Ready())
		return;

	for (UniformDescriptor u : descriptor.VertexShader.Uniforms)
	{
		i32 location = m_shaderProgram.GetUniformLocation(u.name.c_str());

		if (location == -1)
		{
			LogDebug("Shader uniform unused.");
			continue;
		}

		m_uniformLocations.insert({ hash_sv(std::string_view(u.name)), location });
	}
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

i32 Shader::GetUniformLocation(u64 uniformHash)
{
	if (m_uniformLocations.contains(uniformHash))
		return m_uniformLocations[uniformHash];
	return -1;
}

#pragma region Set Uniforms

void Shader::SetUniformMatrix4(u64 uniformHash, Matrix4x4 matrix)
{
	i32 location = GetUniformLocation(uniformHash);

	if (location == -1)
	{
		LogDebug("No such uniform");
		return;
	}

	glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

#pragma endregion