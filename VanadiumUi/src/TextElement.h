#pragma once
#include "Core.h"

class TextElement : public Component
{
public:
	using Component::Component;

	std::string text;
};