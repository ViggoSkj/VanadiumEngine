#pragma once
#include "Core.h"
#include "Style.h"
#include "UiBox.h"

class ScreenElement : public Component
{
public:
	using Component::Component;

	Vanadium::ComponentHandle<ScreenElement> Parent;

	std::vector<ScreenElement*> GetChildren();

	UiBox box;
	ResolvedStyle style;
};