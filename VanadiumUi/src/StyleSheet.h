#pragma once
#include "Style.h"


struct SourceTarget
{
	SourceTarget(std::string_view identifier, StyleSourceType sourceType);

	u64 identifierHash;
	StyleSourceType sourceType;
};

struct SourcedStyle
{
	SourceTarget target;
	Style style;
};

struct StyleSheet
{
public:
	static std::shared_ptr<StyleSheet> LoadFromFile(std::filesystem::path path);

	void PushSourcedStyle(SourceTarget target, Style style);
	std::optional<Style> GetClassDefinition(std::string className);

private:
	std::vector<SourcedStyle> m_styles;
};