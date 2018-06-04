#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "MicroUrlInfo.h"

class DbIdGenerator;

class MicroUrlService
{
public:
	MicroUrlService();
	~MicroUrlService();

	std::string MakeMicroUrl(const char* url);
	std::string ClickUrl(const char* microUrl);
	UrlInfo Stats(const std::string& microUrl) const;
private:
	std::unique_ptr<DbIdGenerator> m_idGenerator;
	std::unordered_map<long, UrlInfo> m_idToUrl;
};