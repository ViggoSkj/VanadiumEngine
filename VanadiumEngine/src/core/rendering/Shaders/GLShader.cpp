#include "pch.h"
#include "GLShader.h"
#include <sstream>
#include <glad/glad.h>
#include <iostream>
#include "core/Debug/Log.h"
#include "ShaderType.h"

namespace Vanadium
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		int VertexStartLine = -1;
		std::string FragmentSource;
		int FragmentStartLine = -1;
	};

	static int GetLineNumber(const char* err)
	{
		int len = strlen(err);
		std::string lineString = "";
		int count = 0;
		for (int i = 0; i < len; i++)
		{
			if (err[i] == ':')
			{
				count++;
				if (count == 2)
				{
					for (int j = 1; j < 100; j++)
					{
						if ('0' <= err[i + j] && err[i + j] <= '9')
							lineString += err[i + j];
						else
							break;
					}
					break;
				}
			}
		}
		if (lineString == "")
			return 0;
		return std::stoi(lineString);
	}

	void LoadShaderSource(std::string source, ShaderProgramSource& sources)
	{
		std::stringstream stream(source);

		ShaderType type = ShaderType::None;

		std::string line;
		int lineNr = 0;

		while (std::getline(stream, line))
		{
			lineNr++;
			if (line == "#shader vertex")
			{
				type = ShaderType::VertexShader;
				sources.VertexStartLine = lineNr;
				continue;
			}
			if (line == "#shader fragment")
			{
				type = ShaderType::FragmentShader;
				sources.FragmentStartLine = lineNr;
				continue;
			}

			switch (type)
			{
			case ShaderType::VertexShader:
			{
				sources.VertexSource.append(line + "\n");
				break;
			}
			case ShaderType::FragmentShader:
			{
				sources.FragmentSource.append(line + "\n");
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

	bool GLShader::LoadSource(std::string source)
	{
		static int  success;
		static char infoLog[512];

		ShaderProgramSource sources;
		LoadShaderSource(source, sources);

		unsigned int vertexShader = CompileShader(sources.VertexSource.c_str(), sources.VertexStartLine, GL_VERTEX_SHADER);
		unsigned int fragmentShader = CompileShader(sources.FragmentSource.c_str(), sources.FragmentStartLine, GL_FRAGMENT_SHADER);

		if (!vertexShader)
		{
			LogDebug("Could not compile vertex shader.");
			return false;
		}

		if (!fragmentShader)
		{
			LogDebug("Could not compile fragment shader.");
			return false;
		}

		GL_CHECK(m_shaderProgramId = glCreateProgram());
		GL_CHECK(glAttachShader(m_shaderProgramId, vertexShader));
		GL_CHECK(glAttachShader(m_shaderProgramId, fragmentShader));
		GL_CHECK(glLinkProgram(m_shaderProgramId));

		GL_CHECK(glUseProgram(m_shaderProgramId));

		GL_CHECK(glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success));

		GL_CHECK(glDeleteShader(vertexShader));
		GL_CHECK(glDeleteShader(fragmentShader));

		if (!success) {
			GL_CHECK(glGetProgramInfoLog(m_shaderProgramId, 512, NULL, infoLog));
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			return true;
		}

		return true;
	}

	int GLShader::GetUniformLocation(const char* name) const
	{
		Use();
		unsigned int id = GL_CHECK(glGetUniformLocation(m_shaderProgramId, name));
		if (id == -1)
			LogDebug("no such uniform");
		return id;
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

	unsigned int GLShader::CompileShader(const char* shaderSource, int startNumber, GLenum type)
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
			int line = GetLineNumber(infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << "(" << line + startNumber << ")" << infoLog << std::endl;
			return 0;
		}

		return shader;
	}
}