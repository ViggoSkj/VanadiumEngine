#include "MapAsset.h"
#include <fstream>

inline std::unordered_map<char, u8> map =
{
	{' ', 0},
	{'#', 1}
};

MapAsset::MapAsset(std::filesystem::path path)
{
	std::fstream stream(path);
		
	if (!stream.is_open())
	{
		throw std::runtime_error("Failed to open map file: " + path.string());
	}

	std::string result;
	std::string line;

	std::vector<i32> types;
	u32 maxWidth = 0;
	u32 height = 0;

	while (std::getline(stream, line))
	{
		height++;
		u32 i = 0;
		for (i; i < line.size(); i++)
		{
			types.push_back(map.at(line[i]));
		}
		types.push_back(-1);
		maxWidth = std::max(maxWidth, i + 1);
	}

	Map.Resize(maxWidth, height);

	u32 y = 0;
	u32 x = 0;
	for (u32 i = 0; i < types.size(); i++)
	{

		if (types[i] == -1)
		{
			y++;
			x = 0;
			continue;
		}

		Map.Set(x, height - y - 1, (u8) types[i]);
		x++;
	}
}