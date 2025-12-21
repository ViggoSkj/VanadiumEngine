#pragma once
#include "pch.h"
#include "FileAsset.h"
#include "core/CoreTypes.h"
#include "core/IO/IFileLoader.h"

struct IFileAssetStore
{
	IFileAssetStore(u32 id)
		: m_id(id) {
	};

	u32 GetId() const { return m_id; };

private:
	u32 m_id;
};

template<typename TFileAsset>
class FileAssetStore : public IFileAssetStore
{
public:
	FileAssetStore()
		: IFileAssetStore(GetAssetTypeId<TFileAsset>()) {
	};

	void FlushAsset(std::filesystem::path path)
	{
		if (m_loadedFileAssets.contains(path.string()))
			m_loadedFileAssets.erase(path.string());
	}

	std::shared_ptr<TFileAsset> GetAsset(std::filesystem::path path)
	{
		if (m_loadedFileAssets.contains(path.string()))
			return m_loadedFileAssets.at(path.string());

		m_loadedFileAssets.insert({ path.string(), std::make_shared<TFileAsset>(path) });
		return m_loadedFileAssets.at(path.string());
	}
private:
	std::unordered_map<std::string, std::shared_ptr<TFileAsset>> m_loadedFileAssets;
};