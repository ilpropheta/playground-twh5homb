// { autofold
#include "MicroUrlService.h"
#include "DbIdGenerator.h"
#include "3rdparty/Shortener.h"
#include <chrono>

using namespace std;

MicroUrlService::MicroUrlService() : m_idGenerator(new DbIdGenerator())
{
}

MicroUrlService::~MicroUrlService()
{
	delete m_idGenerator;
}

std::string MicroUrlService::ClickUrl(const char* microUrl)
{
	string strMicro(microUrl);
	auto secret = strMicro.substr(strMicro.find_last_of('/') + 1);
	auto& url = m_idToUrl[Ext::Shortener::shortURLtoID(secret)];
	url.Clicks++;
	return url.OriginalUrl;
}

UrlInfo MicroUrlService::Stats(const char* microUrl) const
{
	string strMicro(microUrl);
	auto secret = strMicro.substr(strMicro.find_last_of('/') + 1);
	return m_idToUrl.find(Ext::Shortener::shortURLtoID(secret))->second;
}
// }

std::string MicroUrlService::MakeMicroUrl(const char* url)
{
	auto id = m_idGenerator->generate(url);
	auto secret = Ext::Shortener::idToShortURL(id);
	auto microUrl = string("https://micro.url/") + secret;
	m_idToUrl[id] = { url, microUrl, 0 };
	return microUrl;
}