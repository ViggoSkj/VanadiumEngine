#include "GLShader.h"
#include <fstream>
#include <glad/glad.h>
#include <string>
#include <iostream>
#include "ShaderType.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


void LoadShaderSource(std::string path, ShaderProgramSource& source)
{
	std::fstream File(path);

	ShaderType type = ShaderType::None;

	std::string line;

	while (std::getline(File, line))
	{
		if (line == "#shader vertex")
		{
			type = ShaderType::VertexShader;
			continue;
		}
		if (line == "#shader fragment")
		{
			type = ShaderType::FragmentShader;
			continue;
		}

		switch (type)
		{
		case ShaderType::VertexShader:
		{
			source.VertexSource.append(line + "\n");
			break;
		}
		case ShaderType::FragmentShader:
		{
			source.FragmentSource.append(line + "\n");
			break;
		}
		case ShaderType::None:
			break;
		}
	}
}



GLShader::GLShader()
{

}

GLShader::GLShader(const GLShader& other)
	: ReferenceCounting(other), m_shaderProgramId(other.m_shaderProgramId)
{

}

bool GLShader::LoadSource(const char* sourceFile)
{
	static int  success;
	static char infoLog[512];

	ShaderProgramSource source;
	LoadShaderSource(sourceFile, source);

	unsigned int vertexShader = CompileShader(source.VertexSource.c_str(), GL_VERTEX_SHADER);
	unsigned int fragmentShader = CompileShader(source.FragmentSource.c_str(), GL_FRAGMENT_SHADER);

	GL_CHECK(m_shaderProgramId = glCreateProgram());
	GL_CHECK(glAttachShader(m_shaderProgramId, vertexShader));
	GL_CHECK(glAttachShader(m_shaderProgramId, fragmentShader));
	GL_CHECK(glLinkProgram(m_shaderProgramId));

	GL_CHECK(glUseProgram(m_shaderProgramId));

	GL_CHECK(glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success));
	if (!success) {
		GL_CHECK(glGetProgramInfoLog(m_shaderProgramId, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	GL_CHECK(glDeleteShader(vertexShader));
	GL_CHECK(glDeleteShader(fragmentShader));

	return false;
}

int GLShader::GetUniformLocation(const char* name) const
{
	Use();
	return glGetUniformLocation(m_shaderProgramId, name);
}

void GLShader::Use() const
{
	GL_CHECK(glUseProgram(m_shaderProgramId));
}

void GLShader::ConfigureUniformBlock(const char* blockName, unsigned int bindingPoint) const
{
	GL_CHECK(unsigned int blockIndex = glGetUniformBlockIndex(m_shaderProgramId, blockName));
	GL_CHECK(glUniformBlockBinding(m_shaderProgramId, blockIndex, bindingPoint));
}

unsigned int GLShader::CompileShader(const char* shaderSource, GLenum type)
{
	static int  success;
	static char infoLog[512];

	unsigned int shader;
	GL_CHECK(shader = glCreateShader(type));
	GL_CHECK(glShaderSource(shader, 1, &shaderSource, NULL));
	GL_CHECK(glCompileShader(shader));

	GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		GL_CHECK(glGetShaderInfoLog(shader, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	return shader;
}