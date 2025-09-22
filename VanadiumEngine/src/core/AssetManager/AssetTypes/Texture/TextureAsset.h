#pragma once
#include "core/AssetManager/FileAsset.h"
#include "Texture.h"

struct TextureRGBAAsset : public FileAsset
{
public:
	TextureRGBAAsset(std::string path);
	TextureRGBA Texture;
};