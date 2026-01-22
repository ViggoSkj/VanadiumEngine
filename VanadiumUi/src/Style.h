#pragma once
#include "core/CoreTypes.h"
#include "BoxDirections.h"

#include <chrono>
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

enum class StyleUnit
{
	None,
	Pixel,
	Fraction,
};

struct Mesurement
{
	float number;
	StyleUnit unit;
};

namespace StyleLiterals
{
	constexpr Mesurement operator""px(unsigned long long value) noexcept{
		return Mesurement(value, StyleUnit::Pixel);
	}
}

template<typename T>
struct StyleValue
{
	T value = {};
	Rule rule = Rule::Unset;

	StyleValue() = default;

	StyleValue(T value)
		: value(value), rule(Rule::Apply)
	{

	}

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

	bool operator==(const T& other) const noexcept
	{
		return this->rule == Rule::Apply && this->value == other;
	}

	T Or(T fallback) const
	{
		return rule == Rule::Apply ? value : fallback;
	}
};

template<typename T>
struct StyleBox
{
	StyleBox() = default;

	StyleBox(T value)
		: box(value)
	{

	}

	StyleBox(StyleValue<T> value)
		: box(value)
	{

	}

	StyleBox(StyleValue<T> top, StyleValue<T> right, StyleValue<T> bottom, StyleValue<T> left)
		: box(top, right, bottom, left)
	{

	}

	BoxDirections<StyleValue<T>> box;

	BoxDirections<T> Or(T fallback) const
	{
		BoxDirections<T> result;
		result.top = box.top.Or(fallback);
		result.right = box.right.Or(fallback);
		result.bottom = box.bottom.Or(fallback);
		result.left = box.left.Or(fallback);
		return result;
	}
};

struct Style
{
	enum Positioning
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
	StyleValue<Positioning> positioning;
	StyleBox<bool> marginAuto;
	StyleBox<Mesurement> margin;
	StyleBox<Mesurement> border;
	StyleBox<Mesurement> padding;

	StyleValue<bool> widthAuto;
	StyleValue<bool> heightAuto;

	StyleValue<Vector4> backgroundColor;
	StyleValue<Mesurement> xPosition;
	StyleValue<Mesurement> yPosition;
	StyleValue<Mesurement> width;
	StyleValue<Mesurement> height;

	StyleValue<Mesurement> borderRadius;
};

struct ResolvedStyle
{
	ResolvedStyle() = default;

	ResolvedStyle(const Style& style)
	{
		using namespace StyleLiterals;

		display = style.display.Or(Style::Display::Block);
		position = style.positioning.Or(Style::Positioning::Flow);
		marginAuto = style.marginAuto.Or(false);
		margin = style.margin.Or(0px);
		border = style.border.Or(0px);
		padding = style.padding.Or(0px);

		widthAuto = style.widthAuto.Or(false);
		heightAuto = style.heightAuto.Or(false);

		backgroundColor = style.backgroundColor.Or({ 1.0,1.0,1.0,1.0 });
		xPosition = style.xPosition.Or(0px);
		yPosition = style.yPosition.Or(0px);
		width = style.width.Or(0px);
		height = style.height.Or(0px);

		borderRadius = style.borderRadius.Or(0px);
	}

	Style::Display display;
	Style::Positioning position;
	BoxDirections<bool> marginAuto;
	BoxDirections<Mesurement> margin;
	BoxDirections<Mesurement> border;
	BoxDirections<Mesurement> padding;

	bool widthAuto;
	bool heightAuto;

	Vector4 backgroundColor;
	Mesurement xPosition;
	Mesurement yPosition;
	Mesurement width;
	Mesurement height;

	Mesurement borderRadius;
};