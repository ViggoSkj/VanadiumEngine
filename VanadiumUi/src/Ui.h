#pragma once
#include "UiBox.h"
#include <functional>
#include "Core.h"

struct ClickableBox
{
	std::function<void(Vanadium::MouseButtonDownEvent& event)> handler;
	UiBox box;
};