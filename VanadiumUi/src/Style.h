#pragma once
#include "core/CoreTypes.h"
#include "BoxDirections.h"

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

	Position position = Position::Flow;
	Margin margin;
	BoxDirections<i32> padding;

	bool widthAuto = false;
	bool heightAuto = false;

	Vector4 backgroundColor;
	i32 xPosition = 0;
	i32 yPosition = 0;
	i32 width = 0;
	i32 height = 0;
};