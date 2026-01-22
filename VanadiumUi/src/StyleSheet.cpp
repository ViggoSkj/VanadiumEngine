#include "StyleSheet.h"
#include "core/util/StringHash.h"
#include "StyleSheetParser.h"
#include "core/AssetManager/FileAsset.h"

std::shared_ptr<StyleSheet> StyleSheet::LoadFromFile(std::filesystem::path path)
{
	std::expected<std::string, ErrorValue> data = Vanadium::Detail::ReadFile(path);
	if (!data)
		return nullptr;

	return std::make_shared<StyleSheet>(StyleSheetParser::Parse(data.value())->generated);
}

void StyleSheet::PushSourcedStyle(SourceTarget target, Style style)
{
	m_styles.push_back({ target, style });
}

std::optional<Style> StyleSheet::GetClassDefinition(std::string className)
{
	for (const SourcedStyle& style : m_styles)
	{
		if (style.target.sourceType == StyleSourceType::Class && hash_sv(className) == style.target.identifierHash)
			return style.style;
	}

	return std::nullopt;
}

SourceTarget::SourceTarget(std::string_view identifier, StyleSourceType sourceType)
	: identifierHash(hash_sv(identifier)), sourceType(sourceType)
{
	
}