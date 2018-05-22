// { autofold
#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <string_view>
#include "MicroUrlInfo.h"
#include <optional>

class IIdGenerator;
// }

class MicroUrlService
{
public:
	MicroUrlService();
	MicroUrlService(std::unique_ptr<IIdGenerator>);
	~MicroUrlService();
	
	// this is changed
	std::string MakeMicroUrl(std::string_view url, std::chrono::duration<int> urlDuration = std::chrono::hours(24)*365);
	
	std::optional<std::string> ClickUrl(std::string_view microUrl);
	std::optional<UrlInfo> Stats(std::string_view microUrl) const;

	template<typename Action>
	void VisitMicroUrls(Action action) const;
private:
	std::unique_ptr<IIdGenerator> m_idGenerator;
	std::unordered_map<long, UrlInfo> m_idToUrl;
};

template<typename Action>
void MicroUrlService::VisitMicroUrls(Action action) const
{
	for (auto& p : m_idToUrl) // not using structure bindings
		action(p.second);     // to avoid 'unused variable' warning
}
