#pragma once
#include "GLCommon.h"

enum TextureFiltering
{
	Linear = GL_LINEAR,
	Nearest = GL_NEAREST
};

enum TextureWrap
{
	MirroredRepeat = GL_MIRRORED_REPEAT
};

struct TextureConfiguration
{
	TextureFiltering Filtering;
	TextureWrap TopWrap;
	TextureWrap SideWrap;

	TextureConfiguration(TextureFiltering filtering, TextureWrap wrap)
		: Filtering(filtering), TopWrap(wrap), SideWrap(wrap) {
	};
};