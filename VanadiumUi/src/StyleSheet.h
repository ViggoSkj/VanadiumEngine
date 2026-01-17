#pragma once
#include "Style.h"

struct SourcedStyle
{
	u64 identifierHash;
	StyleSource sourceType;
	Style style;
};

struct StyleSheet
{
public:
	std::vector<SourcedStyle> m_styles;
};