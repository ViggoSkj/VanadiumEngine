#include "pch.h"
#include "TextureAsset.h"

namespace Vanadium
{
	std::shared_ptr<TextureRGBAAsset >TextureRGBAAsset::LoadFromFile(std::filesystem::path path)
	{
		std::expected<TextureRGBA, ErrorValue> img = TextureRGBA::LoadFromFile(path, ImageFileFormat::Png);
		if (!img)
			return nullptr;

		std::shared_ptr<TextureRGBAAsset> asset = std::make_shared<TextureRGBAAsset>();
		asset->Texture = img.value();

		return asset;
	}
}