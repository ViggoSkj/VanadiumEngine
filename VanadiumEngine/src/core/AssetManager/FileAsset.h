#pragma once
#include <string>

typedef unsigned int AssetRef;

enum FileAssetType
{
	Image,
	ShaderSource,
};

struct FileAsset
{
	std::string FilePath;
	FileAssetType AssetType;

	FileAsset(std::string filePath, FileAssetType assetType)
		: FilePath(filePath), AssetType(assetType) {
	};
};