#pragma once
#include "pch.h"
#include "Descriptors/ShaderDescriptor.h"
#include "GLShader.h"
#include "UniformObject.h"
#include "core/IO/IFileLoader.h"
#include "core/CoreTypes.h"

namespace Vanadium
{
	class Shader
	{
	public:
		static std::optional<Shader> CreateShader(std::string source, ShaderDescriptor descriptor);

		Shader(std::string source, ShaderDescriptor descriptor);

		// uses the uniform object if it is needed
		bool TryUseUniformObject(UniformObject& object, ShaderType shaderType);

		i32 GetUniformLocation(u64 uniformHash);

		void SetUniformBool(u64 uniformHash, bool value);
		void SetUniformFloat(u64 uniformHash, float value);
		void SetUniformInt(u64 uniformHash, int value);
		void SetUniformVec2(u64 uniformHash, Vector2 value);
		void SetUniformVec3(u64 uniformHash, Vector3 value);
		void SetUniformVec4(u64 uniformHash, Vector4 value);
		void SetUniformMatrix4(u64 uniformHash, Matrix4 matrix);

		void Use() { return m_shaderProgram.Use(); }

		const GLShader& GlShader() { return m_shaderProgram; };
		const ShaderDescriptor& Descriptor() { return m_shaderDescriptor; };
	private:
		ShaderDescriptor m_shaderDescriptor;
		GLShader m_shaderProgram;

		std::unordered_map<u64, i32> m_uniformLocations;
	};
}