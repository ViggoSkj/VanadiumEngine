#pragma once
#include "pch.h"
#include "Components.h"
#include "ScreenElement.h"
#include "Style.h"
#include "UiBox.h"
#include <string_view>

struct TextProperties
{
	std::string text;
};

enum PropType
{
	None,
	Text
};

struct SpecialProperties
{
	std::variant<TextProperties> variant;
};

struct ResolvedNodeProperties
{
	UiBox box;
};

struct UiNode
{
	UiNode* parent = nullptr;
	std::vector<UiNode> children;
	Style style;
	ResolvedNodeProperties resolvedProperties;
	Vanadium::ComponentHandle<ScreenElement> transform;

	SpecialProperties special;
};

struct UiTree
{
	UiNode root;

	std::vector<UiNode*> GetNodes();
};

void CalculateLayout(UiTree& tree);

void ResolveChildren(UiNode& node);