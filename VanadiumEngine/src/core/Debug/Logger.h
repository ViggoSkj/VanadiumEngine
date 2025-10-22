#pragma once
#include "pch.h"

enum LogLevel
{
	Verbose,
	Info,
	Warning,
	Critical
};

class Logger
{
public:
	void Log(std::string message, LogLevel logLevel);
	void SetLogLevel(LogLevel level) { m_logLevel = level; }

private:
	void PrintLine(std::string message);
	std::string LogLevelString(LogLevel level);

	LogLevel m_logLevel;
};
