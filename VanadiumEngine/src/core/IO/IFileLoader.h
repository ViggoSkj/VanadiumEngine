#pragma once
#include "pch.h"


struct IFileLoader
{
	virtual std::string LoadFile(std::filesystem::path path) {};
};