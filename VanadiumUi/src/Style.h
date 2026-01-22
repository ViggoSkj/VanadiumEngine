#pragma once
#include "core/CoreTypes.h"
#include "BoxDirections.h"

enum class StyleSourceType
{
	None,
	Inline,
	Class,
	Id,
	Type,
};

enum Rule
{
	Unset,
	Apply,
};

template<typename T>
struct StyleValue
{
	T value = {};
	Rule rule = Rule::Unset;

	StyleValue& operator =(const T& other)
	{
		value = other;
		rule = Rule::Apply;
		return *this;
	}

	StyleValue& operator=(const Rule& other)
	{
		rule = other;
		return *this;
	}

	bool operator==(const T& other) noexcept
	{
		return *this == other;
	}

	T Or(T fallback) const
	{
		return rule == Rule::Apply ? value : fallback;
	}

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

	StyleValue<Display> display;
	StyleValue<Position> position;
	StyleValue<BoxDirections<bool>> marginAuto;
	StyleValue<BoxDirections<i32>> margin;
	StyleValue<BoxDirections<i32>> border;
	StyleValue<BoxDirections<i32>> padding;

	StyleValue<bool> widthAuto;
	StyleValue<bool> heightAuto;

	StyleValue<Vector4> backgroundColor;
	StyleValue<i32> xPosition;
	StyleValue<i32> yPosition;
	StyleValue<i32> width;
	StyleValue<i32> height;

	StyleValue<i32> borderRadius;
};

struct ResolvedStyle
{
	ResolvedStyle() = default;

	ResolvedStyle(const Style& style)
	{
		display = style.display.Or(Style::Display::Block);
		position = style.position.Or(Style::Position::Flow);
		marginAuto = style.marginAuto.Or(false);
		margin = style.margin.Or(0);
		border = style.border.Or(0);
		padding = style.padding.Or(0);

		widthAuto = style.widthAuto.Or(false);
		heightAuto = style.heightAuto.Or(false);

		backgroundColor = style.backgroundColor.Or({ 1.0,1.0,1.0,1.0 });
		xPosition = style.xPosition.Or(0);
		yPosition = style.yPosition.Or(0);
		width = style.width.Or(0);
		height = style.height.Or(0);

		borderRadius = style.borderRadius.Or(0);
	}

	Style::Display display;
	Style::Position position;
	BoxDirections<bool> marginAuto;
	BoxDirections<i32> margin;
	BoxDirections<i32> border;
	BoxDirections<i32> padding;

	bool widthAuto;
	bool heightAuto;

	Vector4 backgroundColor;
	i32 xPosition;
	i32 yPosition;
	i32 width;
	i32 height;

	i32 borderRadius;
};