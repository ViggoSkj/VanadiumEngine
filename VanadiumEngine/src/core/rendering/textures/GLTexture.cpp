#include "GLTexture.h"
#include "core/rendering/GLCommon.h"

GLTexture::GLTexture()
	: Config(TextureFiltering::Nearest, TextureWrap::MirroredRepeat)
{
	glGenTextures(1, &m_id);
}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &m_id);
}

void GLTexture::AssignTexture(Texture* texture)
{
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetData());
	glGenerateMipmap(GL_TEXTURE_2D);
	glGetError();
	UnBind();
}

void GLTexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
	glGetError();
}

void GLTexture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glGetError();
}

void GLTexture::Use()
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Config.TopWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Config.SideWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Config.Filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Config.Filtering);
}
