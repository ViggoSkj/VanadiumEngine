#pragma once
#include "Core.h"

class SymbolSheet
{
public:
	SymbolSheet(std::filesystem::path path, i32 symbolWidth, i32 symbolHeight);



private:
	u32 m_symbolWidth;
	u32 m_symbolHeight;

	Vanadium::TextureRGBA m_texture;
};