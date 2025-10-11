#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <typeindex>
#include "FileAsset.h"
#include "AssetTypes/Texture/Texture.h"
#include "FileAssetStore.h"

class AssetManager
{
public:
	AssetManager() = default;
	AssetManager(const AssetManager&) = delete;

	template<typename TFileAsset>
	FileAssetStore<TFileAsset>* GetAssetStore()
	{
		for (int i = 0; i < m_assetStores.size(); i++)
		{
			if (m_assetStores[i]->GetId() == GetAssetTypeId<TFileAsset>())
				return static_cast<FileAssetStore<TFileAsset>*>(m_assetStores[i].get());
		}
		// create component store
		std::unique_ptr<FileAssetStore<TFileAsset>> store();
		m_assetStores.push_back(std::make_unique<FileAssetStore<TFileAsset>>());
		return static_cast<FileAssetStore<TFileAsset>*>(m_assetStores.back().get());
	}

	template<typename TFileAsset>
	std::shared_ptr<TFileAsset> GetFileAsset(std::filesystem::path path)
	{
		FileAssetStore<TFileAsset>* store = GetAssetStore<TFileAsset>();
		return store->GetAsset(path);
	}
private:

	std::vector<std::unique_ptr<IFileAssetStore>> m_assetStores;
};
