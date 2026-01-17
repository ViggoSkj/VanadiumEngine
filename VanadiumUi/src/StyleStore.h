#pragma once
#include "Core.h"
#include "Style.h"

struct StyleSourceId
{
	u32 id;
	StyleSource sourceType;
};

class StyleStore
{
public:
	Vanadium::Handle<Style> GetClassStyleHandle(u64 stringHash);
	Style* GetStyleDefinition(Vanadium::Handle<Style> handle);

private:
	Vanadium::HandleStore<Style> m_styles;
};