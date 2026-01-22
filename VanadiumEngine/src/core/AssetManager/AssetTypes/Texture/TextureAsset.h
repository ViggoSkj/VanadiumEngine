#pragma once
#include "pch.h"
#include "core/AssetManager/FileAsset.h"
#include "Texture.h"

namespace Vanadium
{
	struct TextureRGBAAsset
	{
	public:
		static std::shared_ptr<TextureRGBAAsset> LoadFromFile(std::filesystem::path path);
		TextureRGBA Texture;
	};
}