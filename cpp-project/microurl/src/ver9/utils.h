#pragma once
#include <string>
#include <optional>
#include "MicroUrlInfo.h"

long UrlToId(std::string_view microUrl);
std::optional<UrlInfo> NotExpired(const UrlInfo& url);

template<typename MapType, typename GoodAction>
std::optional<UrlInfo> TryLookup(MapType& idToUrl, std::string_view microUrl, GoodAction action)
{
	if (auto it = idToUrl.find(UrlToId(microUrl)); it != end(idToUrl))
	{
		action(it->second);
		return it->second;
	}
	return std::nullopt;
}