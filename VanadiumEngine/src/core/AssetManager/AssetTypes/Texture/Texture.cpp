#include "pch.h"
#include "Texture.h"
#include <iostream>
#include "lodepng/lodepng.h"

namespace Vanadium
{
	std::expected<TextureRGBA, ErrorValue> TextureRGBA::LoadFromFile(std::filesystem::path path, ImageFileFormat format)
	{
		TextureRGBA tex;

		unsigned char* image = NULL;   // will be allocated by lodepng
		unsigned int width, height;
		unsigned int error;

		// Decode from file into an RGBA 8-bit buffer (4 bytes per pixel)
		error = lodepng_decode32_file(&image, &width, &height, path.string().c_str());
		if (error) {
			printf("decoder error %u: %s\n", error, lodepng_error_text(error));
			return std::unexpected(ErrorValue(0, -112323));
		}

		tex.m_data = Array2D<ColorRGBA>((ColorRGBA*)image, width, height);

		return tex;
	}

	void TextureRGBA::Copy(TextureRGBA& destination) const
	{
		m_data.Copy(destination.m_data);
	}
}