#pragma once
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "FileAsset.h"
#include "AssetTypes/Texture/Texture.h"
#include "AssetStore.h"

class AssetManager
{
public:
	template<typename T>
		requires(std::is_base_of_v<FileAsset, T>)
	AssetStore<T>& GetAssetStore()
	{
		static AssetStore<T> store;
		return store;
	}

	template<typename T>
		requires(std::is_base_of_v<FileAsset, T>)
	T& GetAsset(AssetRef ref)
	{
		AssetStore<T>& store = GetAssetStore<T>();
		return store.Get(ref);
	}

	template<typename T>
		requires(std::is_base_of_v<FileAsset, T>)
	AssetRef LoadFileAsset(const char* filePath)
	{
		AssetStore<T>& store = GetAssetStore<T>();
		return store.LoadAsset(filePath);
	}

	template<typename T>
		requires(std::is_base_of_v<FileAsset, T>)
	T& LoadAndGetFileAsset(const char* filePath)
	{
		AssetStore<T>& store = GetAssetStore<T>();
		AssetRef ref = store.LoadAsset(filePath);
		return store.Get(ref);
	}
private:

};
