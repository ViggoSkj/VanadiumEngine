#include "pch.h"
#include "TextureAsset.h"

TextureRGBAAsset::TextureRGBAAsset(std::filesystem::path path)
	: Texture(path, ImageFileFormat::Png)
{
}
