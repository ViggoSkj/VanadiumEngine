#include "pch.h"
#include "ErrorDomainService.h"

namespace Vanadium
{
	i32 ErrorDomainService::RegisterDomain(std::string name)
	{
		ErrorDomainService& service = Get();
		service.m_domainNames.push_back(name);
		return service.m_domainNames.size() - 1;
	}

	std::string_view ErrorDomainService::GetDomainName(i32 domain)
	{
		ErrorDomainService& service = Get();
		return service.m_domainNames[domain];
	}
}