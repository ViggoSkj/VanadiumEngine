#include "StyleSheet.h"
#include "core/util/StringHash.h"

void StyleSheet::PushSourcedStyle(SourceTarget target, Style style)
{
	m_styles.push_back({ target, style });
}

SourceTarget::SourceTarget(std::string_view identifier, StyleSourceType sourceType)
	: identifierHash(hash_sv(identifier)), sourceType(sourceType)
{
	
}