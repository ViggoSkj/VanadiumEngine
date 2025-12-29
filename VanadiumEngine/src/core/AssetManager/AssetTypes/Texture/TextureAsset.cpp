#include "pch.h"
#include "TextureAsset.h"

namespace Vanadium
{
	TextureRGBAAsset::TextureRGBAAsset(std::filesystem::path path)
		: Texture(path, ImageFileFormat::Png)
	{

	}
}