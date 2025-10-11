#pragma once
#include <filesystem>
#include <string>

struct IFileLoader
{
	virtual std::string LoadFile(std::filesystem::path path) {};
};