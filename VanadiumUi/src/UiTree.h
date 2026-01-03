#pragma once
#include "pch.h"
#include "Components.h"
#include "ScreenElement.h"
#include "Style.h"
#include "UiBox.h"

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
};

struct UiTree
{
	UiNode root;

	std::vector<UiNode*> GetNodes();
};

void CalculateLayout(UiTree& tree);

void ResolveChildren(UiNode& node);