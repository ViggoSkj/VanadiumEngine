#pragma once
#include "pch.h"
#include <filesystem>
#include "core/Rendering/Primitives/Color.h"
#include "core/Util/Array2D.h"

enum ImageFileFormat
{
	Png
};

class Texture
{
public:
	Texture() {};
	virtual unsigned int GetWidth() { return 0; };
	virtual unsigned int GetHeight() { return 0; };
	virtual void* GetData() { return nullptr; };
};

class TextureRGBA : public Texture
{
public:
	TextureRGBA(std::filesystem::path path, ImageFileFormat format);

	unsigned int GetWidth() override { return m_data.GetWidth(); }
	unsigned int GetHeight() override { return m_data.GetHeight(); }

	void* GetData() override { return m_data.Data(); }

private:
	Array2D<ColorRGBA> m_data;
};