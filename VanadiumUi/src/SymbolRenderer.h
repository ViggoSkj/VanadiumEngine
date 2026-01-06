#pragma once
#include "SymbolSheet.h"

class SymbolRenderer
{
public:
	SymbolRenderer(std::shared_ptr<SymbolSheet> sheet);

	void Render();

	void SetFontSize(i32 fontSize);
	void SetSymbols(std::string_view symbols, const std::vector<Vector2>& positions);

	std::shared_ptr<SymbolSheet> Sheet();
private:
	void CreateVertexBuffers(const std::vector<Vector2>& uvs, const std::vector<Vector2>& positions);

	VertexArray m_vertexArray;
	VertexBuffer m_uvBuffer;
	VertexBuffer m_positionsBuffer;

	i32 m_symbolCount = 0;

	i32 m_fontSize = 16;
	std::shared_ptr<SymbolSheet> m_sheet;
};