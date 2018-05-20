#pragma once
#include <string>
#include <optional>
#include <functional>
#include "MicroUrlInfo.h"

long UrlToId(std::string_view microUrl);

std::optional<UrlInfo> WhenNotExpired(const UrlInfo& url);

UrlInfo VisitUrl(UrlInfo& url);

template<typename IdToUrlMap>
auto TryLookup(IdToUrlMap& m, std::string_view str)
{
	constexpr bool MapIsConst = std::is_const_v<std::remove_reference_t<decltype(m)>>;
	using UrlInfoType = std::conditional_t<MapIsConst, const UrlInfo, UrlInfo>;
	using OptionalType = std::optional<std::reference_wrapper<UrlInfoType>>;

	auto id = UrlToId(str);
	if (auto it = m.find(id); it != end(m))
	{
		return OptionalType{ it->second };
	}
	return OptionalType{ std::nullopt };
}