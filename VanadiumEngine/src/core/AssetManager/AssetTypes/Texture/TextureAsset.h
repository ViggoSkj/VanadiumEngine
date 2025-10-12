#pragma once
#include "pch.h"
#include "core/AssetManager/FileAsset.h"
#include "Texture.h"

struct TextureRGBAAsset
{
public:
	TextureRGBAAsset(std::filesystem::path path);
	TextureRGBA Texture;
};