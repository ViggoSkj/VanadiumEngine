#pragma once
#include "core/CoreTypes.h"
#include "BoxDirections.h"

enum class StyleSource
{
	None,
	Inline,
	Class,
	Id,
	Type,
};

struct Style
{
	enum Position
	{
		Absolute,
		Flow
	};

	struct Margin
	{
		Margin() = default;

		BoxDirections<bool> marginAuto = { false, false, false, false };
		BoxDirections<i32> margin = { 0, 0, 0, 0 };
	};

	enum Display
	{
		Block,
		Inline,
	};

	Display display = Display::Block;
	Position position = Position::Flow;
	Margin margin;
	BoxDirections<i32> border;
	BoxDirections<i32> padding;

	bool widthAuto = false;
	bool heightAuto = false;

	Vector4 backgroundColor = { 1, 1, 1, 1};
	i32 xPosition = 0;
	i32 yPosition = 0;
	i32 width = 0;
	i32 height = 0;

	i32 borderRadius = 0;
};