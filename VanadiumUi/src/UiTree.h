#pragma once
#include "pch.h"
#include "Components.h"
#include "ScreenTransform.h"

struct NodeStyle
{
	i32 width = 0;
	i32 height = 0;
};

struct ResolvedNodeProperties
{
	i32 width = 0;
	i32 height = 0;
	i32 xPosition = 0;
	i32 yPosition = 0;
};

struct UiNode
{
	std::vector<UiNode> children;
	NodeStyle stlye;
	ResolvedNodeProperties resolvedProperties;
	Vanadium::ComponentHandle<ScreenTransform> transform;
};

struct UiTree
{
	std::shared_ptr<UiNode> root;
};