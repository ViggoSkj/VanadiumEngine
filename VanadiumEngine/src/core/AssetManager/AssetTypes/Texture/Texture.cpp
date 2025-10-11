#include "Texture.h"
#include <iostream>
#include <filesystem>
#include "lodepng/lodepng.h"

TextureRGBA::TextureRGBA(std::filesystem::path path, ImageFileFormat format)
{
    unsigned char* image = NULL;   // will be allocated by lodepng
    unsigned int width, height;
    unsigned int error;

    // Decode from file into an RGBA 8-bit buffer (4 bytes per pixel)
    error = lodepng_decode32_file(&image, &width, &height, path.string().c_str());
    if (error) {
        printf("decoder error %u: %s\n", error, lodepng_error_text(error));
        return;
    }

	m_data = Array2D<ColorRGBA>((ColorRGBA*)image, width, height);
}
