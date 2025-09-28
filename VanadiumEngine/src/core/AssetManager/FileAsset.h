#pragma once
#include <string>
#include <fstream>

struct FileAsset
{
	static std::string ReadFile(std::string file)
	{
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

	FileAsset() {};
	FileAsset(std::string filePath) {};
};

struct AssetRef
{
	AssetRef() = default;
	AssetRef(unsigned int index)
		: BufferIndex(index) {
	};

	bool operator==(const AssetRef& other) const {
		return BufferIndex == other.BufferIndex;
	}

	unsigned int BufferIndex;
};

struct AssetRefHash
{
	std::size_t operator()(const AssetRef& ref) const {
		return ref.BufferIndex;
	}
};