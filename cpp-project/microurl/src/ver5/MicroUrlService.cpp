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

std::string MicroUrlService::ClickUrl(const char* microUrl)
{
	string strMicro(microUrl);
	auto secret = strMicro.substr(strMicro.find_last_of('/') + 1);
	auto& url = m_idToUrl[Ext::Shortener::shortURLtoID(secret.c_str())];
	url.Clicks++;
	return url.OriginalUrl;
}

UrlInfo MicroUrlService::Stats(const std::string& microUrl) const
{
	string strMicro(microUrl);
	auto secret = strMicro.substr(strMicro.find_last_of('/') + 1);
	return m_idToUrl.find(Ext::Shortener::shortURLtoID(secret.c_str()))->second;
}

std::string MicroUrlService::MakeMicroUrl(const char* url)
{
	auto id = m_idGenerator->Generate(url);
	auto secret = Ext::Shortener::idToShortURL(id);
	auto microUrl = string("https://micro.url/") + secret;
	m_idToUrl[id] = { url, microUrl, 0 };
	return microUrl;
}