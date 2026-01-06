#include "SymbolSheet.h"
#include "core/util/StringHash.h"
#include "SymbolSheetMap.h"

SymbolSheet::SymbolSheet(std::filesystem::path path)
	: SymbolSheet(path, 16, 16, 10, 10)
{
}

SymbolSheet::SymbolSheet(std::filesystem::path path, u32 symbolWidth, u32 symbolHeight, u32 columns, u32 rows)
	: m_symbolWidth(symbolWidth)
	, m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/symbol.shader")->CreateShader().value())
	, m_symbolHeight(symbolHeight)
	, m_texture(Vanadium::Rendering::LoadTexture(path))
	, m_columns(columns)
	, m_rows(rows)
{
}

Vector2 SymbolSheet::GetSymbolSize(char symbol, i32 fontSize) const
{
	return GetFontSize(fontSize);
}

Vector2 SymbolSheet::GetSymbolPosition(char symbol) const
{
	i32 index = -1;

	if (CHAR_TO_INDEX.contains(symbol))
		index = CHAR_TO_INDEX.at(symbol);
	else
		return Vector2(-1, -1);

	i32 x = index % m_columns;
	i32 y = index / m_columns;

	assert(0 <= y < m_rows);
	assert(0 <= x < m_columns);

	return Vector2(x, y) / Vector2(m_columns, m_rows);
}

void SymbolSheet::Use(i32 fontSize)
{
	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	Vanadium::Rendering::GetRenderTexture(m_texture)->glTexture.Use();
	Vector2 f = GetFontSize(fontSize);
	m_shader.Use();
	m_shader.SetUniformInt("u_sampler"_id, 0);
	m_shader.SetUniformVec2("u_symbolSize"_id, Vector2(1.0 / m_columns, 1.0 / m_rows));
	m_shader.SetUniformVec4("u_rect"_id, Rect({0,0}, f));
}

Vector2 SymbolSheet::GetFontSize(i32 fontSize) const
{
	return Vector2(fontSize, fontSize) * 3.0f;
}