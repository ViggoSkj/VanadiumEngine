#pragma once
#include "core/AssetManager/AssetTypes/Texture.h"
#include "core/rendering/textures/TextureConfiguration.h"

class GLTexture
{
public:
	GLTexture();
	~GLTexture();

	void AssignTexture(Texture* texture);

	void Bind();
	void UnBind();

	void Use();

	TextureConfiguration Config;
private:
	unsigned int m_id = 0;
};