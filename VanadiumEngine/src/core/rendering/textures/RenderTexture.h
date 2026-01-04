#pragma once
#include "GLTexture.h"
#include "core/AssetManager/AssetTypes/Texture/Texture.h"

namespace Vanadium
{
	struct RenderTexture
	{
		TextureRGBA textureData;
		GLTexture glTexture;
	};
}