#include "SymbolSheet.h"
#include "core/util/StringHash.h"

SymbolSheet::SymbolSheet(std::filesystem::path path, u32 symbolWidth, u32 symbolHeight, u32 columns, u32 rows)
	: m_symbolWidth(symbolWidth)
	, m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/symbol.shader")->CreateShader().value())
	, m_symbolHeight(symbolHeight)
	, m_texture(Vanadium::Rendering::LoadTexture(path))
	, m_columns(columns)
	, m_rows(rows)

{
	m_symbolVao = Vanadium::Rendering::CreateVertexArray(Vanadium::Rendering::CreateMesh(Vanadium::Util::SquareMeshData(2.0)));

	m_uvs.push_back({ 0, 0 });
	m_uvs.push_back({ 1 / 10.0, 0 / 10.0 });
	m_uvData.SetVertecies(m_uvs.data(), m_uvs.size() * sizeof(Vector2), GL_DYNAMIC_DRAW);
	m_symbolVao.AddVertexBuffer({ Vanadium::GLVertexAttribute(GL_FLOAT, 2, GL_FALSE) }, m_uvData, 1, 1);

	m_positions.push_back({ 0, 0 });
	m_positions.push_back({ 1, 0 });
	m_positionData.SetVertecies(m_positions.data(), m_positions.size() * sizeof(Vector2), GL_DYNAMIC_DRAW);
	m_symbolVao.AddVertexBuffer({ Vanadium::GLVertexAttribute(GL_FLOAT, 2, GL_FALSE) }, m_positionData, 2, 1);
}

void SymbolSheet::Use()
{
	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	Vanadium::Rendering::GetRenderTexture(m_texture)->glTexture.Use();
	m_shader.Use();
	m_shader.SetUniformInt("u_sampler"_id, 0);
	m_shader.SetUniformVec2("u_symbolSize"_id, Vector2(1.0 / m_columns, 1.0 / m_rows));
	m_shader.SetUniformVec4("u_rect"_id, Rect({ 100, 100 }, { 200, 200 }));
}

void SymbolSheet::Draw()
{
	m_symbolVao.Bind();
	GL_CHECK(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_positions.size()));
}