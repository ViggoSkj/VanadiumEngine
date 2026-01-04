#pragma once
#include "core/CoreTypes.h"
#include "pch.h"
#include <type_traits>

template<typename T>
class BoxDirections
{
	static constexpr bool has_plus =
		requires(T a, T b) {
			{ a + b } -> std::convertible_to<T>;
	};

public:
	BoxDirections() = default;

	BoxDirections(T top, T right, T down, T left)
		: top(top)
		, right(right)
		, bottom(down)
		, left(left)
	{
	}

	BoxDirections(std::array<T, 4> array)
		: top(array[0])
		, right(array[1])
		, bottom(array[2])
		, left(array[3])
	{

	}

	BoxDirections(T value)
		: top(value)
		, right(value)
		, bottom(value)
		, left(value)
	{

	}

	// i32-only: vertical/horizontal split ctor
	BoxDirections(i32 vertical, i32 horizontal)
		requires (std::is_same_v<T, i32>)
	: top(vertical / 2)
		, right(horizontal / 2)
		, bottom(vertical / 2)
		, left(horizontal / 2)
	{
	}

	// i32-only: construct from Vector4I
	BoxDirections(Vector4I v)
		requires (std::is_same_v<T, i32>)
	: top(v.x)
		, right(v.y)
		, bottom(v.z)
		, left(v.w)
	{
	}

	// keep if you want it for all Ts; or constrain if needed
	bool operator==(const BoxDirections& other) const = default;

	// i32-only: implicit conversion to Vector4I
	operator Vector4I() const
		requires (std::is_same_v<T, i32>)
	{
		return Vector4I(top, right, bottom, left);
	}

	operator Vector4() const
		requires (std::is_same_v<T, i32>)
	{
		return Vector4(top, right, bottom, left);
	}

	T Horizontal() const
		requires has_plus
	{
		return right + left;
	}

	T Vertical() const
		requires has_plus
	{
		return top + bottom;
	}

	T top = 0;
	T right = 0;
	T bottom = 0;
	T left = 0;
};