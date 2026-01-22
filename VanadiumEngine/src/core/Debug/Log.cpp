#include "pch.h"
#include "Log.h"
#include "Application.h"
#include "core/ErrorValue/ErrorDomainService.h"

namespace Vanadium
{
	using Vanadium::Application;

	void LogError(ErrorValue error)
	{
		std::string_view domainName = ErrorDomainService::GetDomainName(error.domain);
		Logger* logger = Application::Get().GetLogger();

		std::string message(domainName);
		message.append("(");
		message.append(std::to_string(error.code));
		message.append("): ");
		message.append(error.message);

		logger->Log(message, LogLevel::Error);
	}

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
}