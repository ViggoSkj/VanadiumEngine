#pragma once
#include "pch.h"

namespace Vanadium
{
	struct ColorRGBA
	{
		operator Vector4()
		{
			return { r, g, b, a };
		}

		u8 r;
		u8 g;
		u8 b;
		u8 a;
	};

	namespace Colors
	{
		inline ColorRGBA white = { 1.0, 1.0, 1.0, 1.0 };
		inline ColorRGBA red = { 1.0, 0.0, 0.0, 1.0 };
	}
};