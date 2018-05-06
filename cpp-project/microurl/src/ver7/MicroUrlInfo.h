// { autofold
#pragma once
#include <string>
#include <tuple>
#include <chrono>
// }

struct UrlInfo
{
	std::string OriginalUrl;
	std::string MicroUrl;
	int Clicks;
	std::chrono::system_clock::time_point CreationDate;
	std::chrono::system_clock::time_point ExpirationDate;
};

inline auto AsTuple(const UrlInfo& info)
{
	return std::tie(info.OriginalUrl, info.MicroUrl, info.Clicks, info.CreationDate, info.ExpirationDate);
}

inline bool operator<(const UrlInfo& left, const UrlInfo& right)
{
	return AsTuple(left) < AsTuple(right);
}