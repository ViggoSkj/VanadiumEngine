#pragma once
#include "Core.h"

class SymbolSheet
{
public:
	static std::shared_ptr<SymbolSheet> LoadFromFile(std::filesystem::path path);

	SymbolSheet(std::filesystem::path path);
	SymbolSheet(std::filesystem::path path, u32 symbolWidth, u32 symbolHeight, u32 columns, u32 rows);

	Vector2 GetSymbolSize(char symbol, i32 fontSize) const;
	Vector2 GetSymbolPosition(char symbol) const;

	void Use(i32 fontSize);
private:
	Vector2 GetFontSize(i32 fontSize) const;

	Shader m_shader;
	Vanadium::RenderTextureHandle m_texture;
	u32 m_symbolWidth;
	u32 m_symbolHeight;
	u32 m_columns;
	u32 m_rows;
};