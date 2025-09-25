
#pragma once
#include "core/Rendering/Color.h"
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
	TextureRGBA(const char* file, ImageFileFormat format);

	unsigned int GetWidth() override { return m_data.GetWidth(); }
	unsigned int GetHeight() override { return m_data.GetHeight(); }

	void* GetData() override { return m_data.Data(); }

private:
	Array2D<ColorRGBA> m_data;
};