#pragma once
#include <vector>
#include <unordered_map>
#include "FileAsset.h"
#include "AssetTypes/Texture.h"

class AssetManager
{
public:
	AssetRef AddFileAsset(FileAsset asset);
	void FreeAsset(AssetRef assetSlot);

	std::shared_ptr<Texture> LoadTexture(AssetRef imageAsset);

private:
	std::vector<FileAsset> m_fileAssets;
	std::vector<AssetRef> m_freeAssetSlots;

	std::unordered_map<AssetRef, std::shared_ptr<Texture>> m_imageTextures;
};