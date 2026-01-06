#include "SymbolRenderer.h"

SymbolRenderer::SymbolRenderer(std::shared_ptr<SymbolSheet>  sheet)
	: m_sheet(sheet)
	, m_vertexArray(Vanadium::Rendering::CreateVertexArray(Vanadium::Rendering::CreateMesh(Vanadium::Util::SquareMeshData(2.0, false))))
{
	m_vertexArray.AddVertexBuffer({ Vanadium::GLVertexAttribute(GL_FLOAT, 2, GL_FALSE) }, m_uvBuffer, 1, 1);
	m_vertexArray.AddVertexBuffer({ Vanadium::GLVertexAttribute(GL_FLOAT, 2, GL_FALSE) }, m_positionsBuffer, 2, 1);
}

void SymbolRenderer::Render()
{
	m_sheet->Use(m_fontSize);
	m_vertexArray.Bind();
	GL_CHECK(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_symbolCount));
}

void SymbolRenderer::SetFontSize(i32 fontSize)
{
	m_fontSize = fontSize;
}

void SymbolRenderer::SetSymbols(std::string_view symbols, const std::vector<Vector2>& positions)
{
	assert(symbols.size() == positions.size());

	std::vector<Vector2> uvData(symbols.size());
	for (i32 i = 0; i < symbols.size(); i++)
	{
		Vector2 uvStart = m_sheet->GetSymbolPosition(symbols[i]);
		uvData[i] = uvStart;
	}

	CreateVertexBuffers(uvData, positions);
}

std::shared_ptr<SymbolSheet> SymbolRenderer::Sheet()
{
	return m_sheet;
}

void SymbolRenderer::CreateVertexBuffers(const std::vector<Vector2>& uvs, const std::vector<Vector2>& positions)
{
	assert(uvs.size() == positions.size());
	m_symbolCount = uvs.size();
	m_uvBuffer.SetVertecies(uvs, GL_DYNAMIC_DRAW);
	m_positionsBuffer.SetVertecies(positions, GL_DYNAMIC_DRAW);
}