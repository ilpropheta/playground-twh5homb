// { autofold
#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <string_view>
#include "MicroUrlInfo.h"

class IIdGenerator;

class MicroUrlService
{
public:
	MicroUrlService();
	MicroUrlService(std::unique_ptr<IIdGenerator>);
	~MicroUrlService();

	std::string MakeMicroUrl(std::string_view url);
	std::string ClickUrl(std::string_view microUrl);
	UrlInfo Stats(std::string_view microUrl) const;
// }

	//...write a visit-like function here...;

private:
	std::unique_ptr<IIdGenerator> m_idGenerator;
	std::unordered_map<long, UrlInfo> m_idToUrl;
};