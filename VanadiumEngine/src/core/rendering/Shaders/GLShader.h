#pragma once

#include "GLCommon.h"
#include "core/Util/ReferenceCounting.h"

class GLShader : public ReferenceCounting
{
public:
	GLShader();
	GLShader(const GLShader& other);

	unsigned int GetId() const {
		return m_shaderProgramId;
	};
	bool LoadSource(std::string source);
	int GetUniformLocation(const char* name) const;
	void Use() const;
	void ConfigureUniformBlock(const char* blockName, unsigned int bindingPoint) const;

protected:
	void Dispose() override {
		GL_CHECK(glDeleteProgram(m_shaderProgramId));
	};

private:
	unsigned int m_shaderProgramId = 0;
	unsigned int CompileShader(const char* shaderSource, int lineNumber, GLenum type);
};