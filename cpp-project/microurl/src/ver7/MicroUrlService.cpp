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

long UrlToId(string_view microUrl)
{
	auto secret = microUrl.substr(microUrl.find_last_of('/') + 1);
	return Ext::Shortener::shortURLtoID(secret.data());
}

std::optional<std::string> MicroUrlService::ClickUrl([[maybe_unused]]std::string_view microUrl)
{
	// implement this properly
	return {};
}

std::optional<UrlInfo> MicroUrlService::Stats([[maybe_unused]]std::string_view microUrl) const
{
	// implement this properly
	return {};
}

// { autofold
std::string MicroUrlService::MakeMicroUrl(std::string_view url)
{
	auto id = m_idGenerator->Generate(url.data());
	auto secret = Ext::Shortener::idToShortURL(id);
	auto microUrl = string("https://micro.url/") + secret;
	m_idToUrl[id] = { {url.data(), url.size()}, microUrl, 0 };
	return microUrl;
}
// }