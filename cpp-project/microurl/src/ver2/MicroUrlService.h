#pragma once
#include <string>
#include <unordered_map>
#include "MicroUrlInfo.h"

class IIdGenerator;

class MicroUrlService
{
public:
	MicroUrlService(IIdGenerator* gen);
	~MicroUrlService();

	std::string MakeMicroUrl(const char* url);
	std::string ClickUrl(const char* microUrl);
	UrlInfo Stats(const char* microUrl) const;
private:
	IIdGenerator * m_idGenerator;
	std::unordered_map<long, UrlInfo> m_idToUrl;
};