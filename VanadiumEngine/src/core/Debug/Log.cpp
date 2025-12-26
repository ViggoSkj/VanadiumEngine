#include "pch.h"
#include "Log.h"
#include "Application.h"

using Vanadium::Application;

void LogDebug(std::string message)
{
	Logger* logger = Application::Get().GetLogger();
	logger->Log(message, LogLevel::Verbose);
}

void LogInfo(std::string message)
{
	Logger* logger = Application::Get().GetLogger();
	logger->Log(message, LogLevel::Info);
}