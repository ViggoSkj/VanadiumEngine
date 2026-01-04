#pragma once
#include "Core.h"

class SymbolSheet
{
public:
	SymbolSheet(std::filesystem::path path, u32 symbolWidth, u32 symbolHeight, u32 columns, u32 rows);

	void Use();

	void Draw();
private:
	Shader m_shader;
	Vanadium::RenderTextureHandle m_texture;
	u32 m_symbolWidth;
	u32 m_symbolHeight;
	u32 m_columns;
	u32 m_rows;

	VertexArray m_symbolVao;
	VertexBuffer m_uvData;
	VertexBuffer m_positionData;
	std::vector<Vector2> m_uvs;
	std::vector<Vector2> m_positions;
};