#pragma once
#include "pch.h"
#include "Components.h"
#include "ScreenElement.h"
#include "Style.h"
#include "UiBox.h"
#include "SymbolRenderer.h"

struct TextProperties
{
	std::shared_ptr<SymbolRenderer> renderer;
	std::string text;
	std::vector<Vector2> resolvedPositions;
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
	std::shared_ptr<UiNode> parent = nullptr;
	std::vector<std::shared_ptr<UiNode>> children;
	ResolvedStyle style;
	ResolvedNodeProperties resolvedProperties;
	Vanadium::ComponentHandle<ScreenElement> transform;

	SpecialProperties special;
};

struct UiTree
{
	Vector2I screenResolution;

	std::shared_ptr<UiNode> root;

	std::vector<std::shared_ptr<UiNode>> GetNodes();
};

void CalculateLayout(UiTree& tree);

void ResolveChildren(std::shared_ptr<UiNode> node);