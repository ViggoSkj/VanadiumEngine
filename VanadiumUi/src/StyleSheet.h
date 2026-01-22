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
	void PushSourcedStyle(SourceTarget target, Style style);

private:
	std::vector<SourcedStyle> m_styles;
};