#pragma once
#include "core/Util/UnorderdVector.h"
#include "core/CoreTypes.h"	

struct PixelSoa
{
	void Add(i32 x, i32 y, u8 type)
	{
		XPositions.push_back(x);
		YPositions.push_back(y);
		Types.push_back(type);
	}

	Vector2 Position(u32 index) const
	{
		return Vector2{ static_cast<float>(XPositions[index]), static_cast<float>(YPositions[index]) };
	}

	u32 Count() const { return XPositions.size(); }
	UnorderedVector<i32> YPositions;
	UnorderedVector<i32> XPositions;
	UnorderedVector<u8> Types;
};