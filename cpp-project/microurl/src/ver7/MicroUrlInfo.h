// { autofold
#pragma once
#include <string>
#include <tuple>
// }

struct UrlInfo
{
	std::string OriginalUrl;
	std::string MicroUrl;
	int Clicks;
};

inline auto AsTuple(const UrlInfo& info)
{
	return std::tie(info.OriginalUrl, info.MicroUrl, info.Clicks);
}

inline bool operator<(const UrlInfo& left, const UrlInfo& right)
{
	return AsTuple(left) < AsTuple(right);
}