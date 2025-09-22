#pragma once
#include "FileAsset.h"
#include <vector>
#include <iostream>

template<typename T>
	requires(std::is_base_of_v<FileAsset, T>)
class AssetStore
{
public:
	AssetStore() {};
	AssetStore(AssetStore&) = delete;

	T& Get(AssetRef ref)
	{
		return m_assets[ref.BufferIndex];
	}

	AssetRef LoadAsset(std::string filePath)
	{
		m_assets.emplace_back(T(filePath));
		return AssetRef(m_assets.size() - 1);
	}

private:
	std::vector<T> m_assets;
};