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

long UrlToId(string_view microUrl)
{
	auto secret = microUrl.substr(microUrl.find_last_of('/') + 1);
	return Ext::Shortener::shortURLtoID(secret.data());
}

template<typename IdToUrlMap>
auto TryLookup(IdToUrlMap& m, string_view str)
{
	constexpr bool MapIsConst = std::is_const_v<std::remove_reference_t<decltype(m)>>;
	using UrlInfoType = std::conditional_t<MapIsConst, const UrlInfo, UrlInfo>;
	using OptionalType = std::optional<std::reference_wrapper<UrlInfoType>>;
	
	auto id = UrlToId(str);
	if (auto it = m.find(id); it != end(m))
	{
		return OptionalType{ it->second };
	}
	return OptionalType{ nullopt };
}
// }

std::optional<std::string> MicroUrlService::ClickUrl(std::string_view microUrl)
{
	return 
		TryLookup(m_idToUrl, microUrl)
		|| [](auto& url) { url.Clicks++; return url; }
		|| &UrlInfo::OriginalUrl;
}

std::optional<UrlInfo> MicroUrlService::Stats(std::string_view microUrl) const
{
	return TryLookup(m_idToUrl, microUrl);
}

std::string MicroUrlService::MakeMicroUrl(std::string_view url, std::chrono::duration<int> urlDuration)
{
	auto id = m_idGenerator->Generate(url.data());
	auto secret = Ext::Shortener::idToShortURL(id);
	auto microUrl = string("https://micro.url/") + secret;
	m_idToUrl[id] = { {url.data(), url.size()}, microUrl, 0 };
	return microUrl;
}