#pragma once
#include "core/CoreTypes.h"
#include <string>
#include <fstream>
#include <filesystem>
#include <concepts>

template<typename T>
concept LoadableAsset = requires(std::filesystem::path path) {
	{ T(path) }; // T must be constructible from std::filesystem::path
	{ std::declval<T>().Load(path) }; // optional if you want a Load() method
};

namespace FileAsset
{
	static std::string ReadFile(std::filesystem::path file)
	{

		if (!std::filesystem::exists(file))
		{
			std::filesystem::path sub("../VanadiumEngine/");
			sub += file;
			file = sub;
		}

		std::fstream stream(file);
		std::string result;
		std::string line;

		while (std::getline(stream, line))
		{
			result.append(line);
			result.push_back('\n');
		}

		return result;
	}
};


template<typename TAsset>
struct AssetTypeId
{
	static u32 Id;
};

template<typename TAsset>
inline u32 AssetTypeId<TAsset>::Id;

template<typename TAsset>
u32 GetAssetTypeId()
{
	return reinterpret_cast<u32>(&AssetTypeId<TAsset>::Id);
}