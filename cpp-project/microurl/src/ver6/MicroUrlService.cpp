// { autofold
#include "MicroUrlService.h"
#include "DbIdGenerator.h"
#include "3rdparty/Shortener.h"

using namespace std;

MicroUrlService::MicroUrlService(std::unique_ptr<IIdGenerator> gen) : m_idGenerator(std::move(gen))
{
}

MicroUrlService::MicroUrlService() : m_idGenerator(std::make_unique<DbIdGenerator>())
{
}

MicroUrlService::~MicroUrlService() = default;
// }

std::string MicroUrlService::ClickUrl(std::string_view microUrl)
{
	auto secret = microUrl.substr(microUrl.find_last_of('/') + 1);
	auto& url = m_idToUrl[Ext::Shortener::shortURLtoID(secret.data())];
	url.Clicks++;
	return url.OriginalUrl;
}

UrlInfo MicroUrlService::Stats(std::string_view microUrl) const
{
	auto secret = microUrl.substr(microUrl.find_last_of('/') + 1);
	return m_idToUrl.find(Ext::Shortener::shortURLtoID(secret.data()))->second;
}

std::string MicroUrlService::MakeMicroUrl(std::string_view url)
{
	auto id = m_idGenerator->Generate(url.data());
	auto secret = Ext::Shortener::idToShortURL(id);
	auto microUrl = string("https://micro.url/") + secret;
	m_idToUrl[id] = { {url.data(), url.size()}, microUrl, 0 };
	return microUrl;
}