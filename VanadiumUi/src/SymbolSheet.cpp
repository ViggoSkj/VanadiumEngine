#include "SymbolSheet.h"

SymbolSheet::SymbolSheet(std::filesystem::path path, i32 symbolWidth, i32 symbolHeight)
	: m_symbolWidth(symbolWidth)
	, m_symbolHeight(symbolHeight)
	, m_texture(Application::Get().GetAssetManager()->GetFileAsset<TextureRGBAAsset>(path)->Texture)
{

}