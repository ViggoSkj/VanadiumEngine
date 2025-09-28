#pragma once
#include "core/AssetManager/AssetTypes/Texture/Texture.h"
#include "core/Rendering/textures/TextureConfiguration.h"

class GLTexture
{
public:
	GLTexture();
	GLTexture(const GLTexture&) = delete;
	~GLTexture();

	void AssignTexture(Texture* texture);

	void Bind();
	void UnBind();

	void Use();

	TextureConfiguration Config;
private:
	unsigned int m_id = 0;
};