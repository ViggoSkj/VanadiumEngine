#pragma once
#include "pch.h"
#include "core/Util/Array2D.h"

class MapAsset
{
public:
	MapAsset(std::filesystem::path path);

	Array2D<u8> Map;
};