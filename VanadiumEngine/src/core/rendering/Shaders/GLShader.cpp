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

	m_shaderProgramId = glCreateProgram();
	glAttachShader(m_shaderProgramId, vertexShader);
	glAttachShader(m_shaderProgramId, fragmentShader);
	glLinkProgram(m_shaderProgramId);

	glUseProgram(m_shaderProgramId);

	glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgramId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return false;
}

int GLShader::GetUniformLocation(const char* name) const
{
	Use();
	return glGetUniformLocation(m_shaderProgramId, name);
}

void GLShader::Use() const
{
	glUseProgram(m_shaderProgramId);
}

void GLShader::ConfigureUniformBlock(const char* blockName, unsigned int bindingPoint) const
{
	unsigned int blockIndex = glGetUniformBlockIndex(m_shaderProgramId, blockName);
	glUniformBlockBinding(m_shaderProgramId, blockIndex, bindingPoint);
}

unsigned int GLShader::CompileShader(const char* shaderSource, GLenum type)
{
	static int  success;
	static char infoLog[512];

	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	return shader;
}