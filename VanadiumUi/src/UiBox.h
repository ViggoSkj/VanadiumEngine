#pragma once
#include "core/CoreTypes.h"
#include "BoxDirections.h"

struct UiBox
{
	UiBox() = default;
	UiBox(Vector2I position, Vector2I marign, Vector2I border, Vector2I padding, Vector2I content)
		: position(position)
		, margin(margin)
		, border(Vector4I(border.y, border.x, border.y, border.x))
		, padding(Vector4I(padding.y, padding.x, padding.y, padding.x))
		, content(content)
	{

	}

	void AdjustSize(Vector2I newVisible);

	Vector2I Visible()
	{
		return Vector2I(
			border.Horizontal() + padding.Horizontal() + content.x,
			border.Vertical() + padding.Vertical() + content.y
		);
	}

	Vector2 Full()
	{
		return Vector2I(
			margin.Horizontal() + border.Horizontal() + padding.Horizontal() + content.x,
			margin.Vertical() + border.Vertical() + padding.Vertical() + content.y
		);
	}

	Vector2I position = { 0.0, 0.0 };

	BoxDirections<i32> margin = { 0, 0, 0, 0 };
	BoxDirections<i32> border = { 0, 0, 0, 0 };
	BoxDirections<i32> padding = { 0, 0, 0, 0 };

	Vector2I content = { 0.0, 0.0 };
};