#pragma once
#include <string>
#include "core/CoreTypes.h"

class ErrorValue
{
public:
	ErrorValue(i32 domain, i32 code)
		: domain(domain), code(code)
	{

	}

	ErrorValue(i32 domain, i32 code, std::string_view message)
		: domain(domain), code(code), message(message)
	{

	}

	std::string message;
	i32 code;
	i32 domain;
};