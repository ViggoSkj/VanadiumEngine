#include "AssetManager.h"

AssetRef AssetManager::AddFileAsset(FileAsset asset)
{
	if (m_freeAssetSlots.size() < 1)
	{
		m_fileAssets.push_back(asset);
		return m_fileAssets.size() - 1;
	}
	else
	{
		AssetRef next = m_freeAssetSlots.back();
		m_fileAssets[next] = asset;
		return next;
	}
}

void AssetManager::FreeAsset(AssetRef assetSlot)
{
	m_freeAssetSlots.push_back(assetSlot);
}

std::shared_ptr<Texture> AssetManager::LoadTexture(AssetRef ref)
{
	if (m_imageTextures.contains(ref))
	{
		// already loaded
		return m_imageTextures.at(ref);
	}
	else
	{
		// load texture

		FileAsset asset = m_fileAssets[ref];

		if (asset.FilePath.ends_with(".png"))
		{
			TextureRGBA tex(asset.FilePath.c_str(), ImageFileFormat::Png);
			m_imageTextures.insert({ ref, std::make_shared<TextureRGBA>(tex)});
			return std::make_shared<TextureRGBA>(tex);
		}
	}
}
