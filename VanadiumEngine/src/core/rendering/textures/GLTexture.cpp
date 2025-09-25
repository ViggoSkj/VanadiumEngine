#include "GLTexture.h"
#include "core/rendering/GLCommon.h"

GLTexture::GLTexture()
	: Config(TextureFiltering::Nearest, TextureWrap::MirroredRepeat)
{
	GL_CHECK(glGenTextures(1, &m_id));
}

GLTexture::~GLTexture()
{
	GL_CHECK(glDeleteTextures(1, &m_id));
}

void GLTexture::AssignTexture(Texture* texture)
{
	Bind();
	GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetData()));
	GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
	GL_CHECK(glGetError());
	UnBind();
}

void GLTexture::Bind()
{
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_id));
}

void GLTexture::UnBind()
{
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

void GLTexture::Use()
{
	Bind();
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Config.TopWrap));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Config.SideWrap));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Config.Filtering));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Config.Filtering));
}
