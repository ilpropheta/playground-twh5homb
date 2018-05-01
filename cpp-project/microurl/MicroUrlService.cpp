#include "MicroUrlService.h"
#include "IIdGenerator.h"
#include "Utils.h"
#include <chrono>

using namespace std;

MicroUrlService::MicroUrlService(IIdGenerator* gen) : m_idGenerator(gen)
{
}

MicroUrlService::~MicroUrlService()
{
	delete m_idGenerator;
}

std::string MicroUrlService::MakeMicroUrl(const char* url)
{
	auto id = m_idGenerator->Generate(url);
	auto secret = MicroUrl::Utils::idToShortURL(id);
	auto microUrl = string("http://micro.url/") + secret;
	m_idToUrl[id] = { url, microUrl, 0 };
	return microUrl;
}

std::string MicroUrlService::ClickUrl(const char* microUrl)
{
	string strMicro(microUrl);
	auto secret = strMicro.substr(strMicro.find_last_of('/') + 1);
	auto& url = m_idToUrl[MicroUrl::Utils::shortURLtoID(secret)];
	url.Clicks++;
	return url.OriginalUrl;
}

UrlInfo MicroUrlService::Stats(const char* microUrl) const
{
	string strMicro(microUrl);
	auto secret = strMicro.substr(strMicro.find_last_of('/') + 1);
	return m_idToUrl.find(MicroUrl::Utils::shortURLtoID(secret))->second;
}
