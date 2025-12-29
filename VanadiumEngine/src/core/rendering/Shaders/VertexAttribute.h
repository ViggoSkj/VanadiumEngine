#pragma once
#include "ShaderDataType.h"

namespace Vanadium
{
	struct VertexAttribute
	{
		ShaderDataType Type;
		unsigned int Location;

		VertexAttribute(ShaderDataType type, unsigned int location)
			: Type(type), Location(location) {
		};
	};
}