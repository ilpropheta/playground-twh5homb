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

std::optional<std::string> MicroUrlService::ClickUrl(std::string_view microUrl)
{
	return
		TryLookup(m_idToUrl, microUrl)
		|| WhenNotExpired
		|| VisitUrl
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
	auto now = chrono::system_clock::now();
	auto expiration = now + urlDuration;
	m_idToUrl[id] = { {url.data(), url.size()}, microUrl, 0, now, expiration };
	return microUrl;
}