#pragma once
#include <string>

struct FileAsset
{
	FileAsset() {};
	FileAsset(std::string filePath) {};
};

struct AssetRef
{
	AssetRef(unsigned int index)
		: BufferIndex(index) {
	};

	unsigned int BufferIndex;
};