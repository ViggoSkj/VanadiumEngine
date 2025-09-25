#pragma once
#include "core/rendering/GLCommon.h"
#include "core/util/ReferenceCounting.h"

class GLShader : public ReferenceCounting
{
public:
	GLShader();
	GLShader(const GLShader& other);

	unsigned int GetId() const {
		return m_shaderProgramId;
	};
	bool LoadSource(const char* sourceFile);
	int GetUniformLocation(const char* name) const;
	void Use() const;
	void ConfigureUniformBlock(const char* blockName, unsigned int bindingPoint) const;

protected:
	void Dispose() override {
		glDeleteProgram(m_shaderProgramId);
	};

private:
	unsigned int m_shaderProgramId = 0;
	unsigned int CompileShader(const char* shaderSource, GLenum type);
};