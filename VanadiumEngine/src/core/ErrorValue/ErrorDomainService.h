#pragma once
#include <string>
#include <vector>
#include <memory>
#include "core/CoreTypes.h"

namespace Vanadium
{
	class ErrorDomainService
	{
	public:
		static i32 RegisterDomain(std::string name);
		static std::string_view GetDomainName(i32 domain);

	private:
		static inline std::unique_ptr<ErrorDomainService> s_instance = nullptr;
		static ErrorDomainService& Get()
		{
			if (s_instance == nullptr)
				s_instance = std::make_unique<ErrorDomainService>(ErrorDomainService());
			return *s_instance.get();
		}

		ErrorDomainService()
		{

		}

		i32 m_nextDomainId = 0;
		std::vector<std::string> m_domainNames;
	};
}