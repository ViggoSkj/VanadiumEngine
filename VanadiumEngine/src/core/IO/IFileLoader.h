#pragma once
#include "pch.h"
#include <filesystem>


struct IFileLoader
{
	virtual std::string LoadFile(std::filesystem::path path) {};
};