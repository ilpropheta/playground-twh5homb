#include "Utils.h"
#include "3rdparty/Shortener.h"

long UrlToId(std::string_view microUrl)
{
	auto secret = microUrl.substr(microUrl.find_last_of('/') + 1);
	return Ext::Shortener::shortURLtoID(secret.data());
}

std::optional<std::reference_wrapper<UrlInfo>> GoodIfNotExpired(UrlInfo& url)
{
	if (IsExpired(url))
		return url;
	return std::nullopt;
}