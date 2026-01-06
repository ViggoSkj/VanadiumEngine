#pragma once
#include "Core.h"
#include "SymbolRenderer.h"

class TextElement : public Component
{
public:
	using Component::Component;

	std::string text;
	std::shared_ptr<SymbolRenderer> symbolRenderer;
};