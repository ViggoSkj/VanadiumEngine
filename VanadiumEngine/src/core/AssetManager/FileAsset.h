#pragma once
#include <expected>
#include <fstream>
#include <concepts>
#include "core/CoreTypes.h"
#include "core/ErrorValue/ErrorValue.h"


namespace Vanadium::Detail
{
	inline const i32 FileIODomain = ErrorDomainService::RegisterDomain("FileIODomain");

	enum class FileIOErrorCode
	{
		FailedOpen,
	};

	template<typename T>
	concept LoadableAsset = requires(std::filesystem::path path) {
		{ T(path) }; // T must be constructible from std::filesystem::path
		{ std::declval<T>().Load(path) }; // optional if you want a Load() method
	};

	static std::expected<std::string, ErrorValue> ReadFile(std::filesystem::path file)
	{
		if (!std::filesystem::exists(file))
		{
			std::filesystem::path sub("../VanadiumEngine/");
			sub += file;
			file = sub;
		}

		std::fstream stream(file);

		if (!stream.is_open())
		{
			std::string msg = "Failed to open file: ";
			msg.append(file.string());
			return std::unexpected(ErrorValue(FileIODomain, (i32)FileIOErrorCode::FailedOpen, msg));
		}

		std::string result;
		std::string line;

		while (std::getline(stream, line))
		{
			result.append(line);
			result.push_back('\n');
		}

		return result;
	}

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
};