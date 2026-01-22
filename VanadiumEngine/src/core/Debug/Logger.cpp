#include "pch.h"
#include "Logger.h"
#include <iostream>

namespace Vanadium
{
	void Logger::Log(std::string message, LogLevel logLevel)
	{
		if (logLevel >= m_logLevel)
		{
			std::string log = "(";
			log.append(LogLevelString(logLevel));
			log.append(")");
			log.append(" ");
			log.append(message);
			PrintLine(log);
		}
	}

	void Logger::PrintLine(std::string message)
	{
		std::cout << message << std::endl;
	}

	std::string Logger::LogLevelString(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Verbose:
			return "Verbose";
		case LogLevel::Info:
			return "Info";
		case LogLevel::Warning:
			return "Warning";
		case LogLevel::Error:
			return "Error";
		case LogLevel::Critical:
			return "Critical";
		default:
			return "LOG_LEVEL_NOT_SET";
		}
	}

}