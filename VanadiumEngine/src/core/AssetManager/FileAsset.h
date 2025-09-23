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
	AssetRef(unsigned int index)
		: BufferIndex(index) {
	};

	unsigned int BufferIndex;
};