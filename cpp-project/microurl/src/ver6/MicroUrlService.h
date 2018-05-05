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

	template<typename Action>
	void VisitMicroUrls(Action action) const;

private:
	std::unique_ptr<IIdGenerator> m_idGenerator;
	std::unordered_map<long, UrlInfo> m_idToUrl;
};

template<typename Action>
void MicroUrlService::VisitMicroUrls(Action action) const
{
	for (auto&[id, url] : m_idToUrl)
		action(url);
	//throw std::logic_error("missing function");
}
