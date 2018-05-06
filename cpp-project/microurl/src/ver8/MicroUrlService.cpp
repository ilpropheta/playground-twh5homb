// { autofold
#include "MicroUrlService.h"
#include "DbIdGenerator.h"
#include "3rdparty/Shortener.h"
#include "3rdparty/optionalUtils.h"

using namespace std;

MicroUrlService::MicroUrlService(std::unique_ptr<IIdGenerator> gen) : m_idGenerator(std::move(gen))
{
}

MicroUrlService::MicroUrlService() : m_idGenerator(std::make_unique<DbIdGenerator>())
{
}

MicroUrlService::~MicroUrlService() = default;
// }

long UrlToId(string_view microUrl)
{
	auto secret = microUrl.substr(microUrl.find_last_of('/') + 1);
	return Ext::Shortener::shortURLtoID(secret.data());
}

template<typename MapType, typename GoodAction>
std::optional<UrlInfo> TryLookup(MapType& idToUrl, string_view microUrl, GoodAction action)
{
	if (auto it = idToUrl.find(UrlToId(microUrl)); it != end(idToUrl))
	{
		action(it->second);
		return it->second;
	}
	return nullopt;
}

optional<UrlInfo> NotExpired(const UrlInfo& url)
{
	return url;
}

std::optional<std::string> MicroUrlService::ClickUrl(std::string_view microUrl)
{
	return TryLookup(m_idToUrl, microUrl, [](auto& url) { url.Clicks++; })
		|| [](auto& url) {return url.OriginalUrl; };
		
	
	/*if (auto opt = TryLookup(m_idToUrl, microUrl, [](auto& url) { url.Clicks++; }); opt)
		return opt->OriginalUrl;
	return nullopt;*/
}

std::optional<UrlInfo> MicroUrlService::Stats(std::string_view microUrl) const
{
	return TryLookup(m_idToUrl, microUrl, [](auto&) {});
}

std::string MicroUrlService::MakeMicroUrl(std::string_view url)
{
	auto id = m_idGenerator->Generate(url.data());
	auto secret = Ext::Shortener::idToShortURL(id);
	auto microUrl = string("https://micro.url/") + secret;
	m_idToUrl[id] = { {url.data(), url.size()}, microUrl, 0 };
	return microUrl;
}