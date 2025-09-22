#include "TextureAsset.h"

TextureRGBAAsset::TextureRGBAAsset(std::string path)
	: Texture(path.c_str(), ImageFileFormat::Png)
{
}
