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
	std::chrono::system_clock::time_point Creation;
	std::chrono::system_clock::time_point Expiration;
};

inline auto AsTuple(const UrlInfo& info)
{
	return std::tie(info.OriginalUrl, info.MicroUrl, info.Clicks, info.Creation, info.Expiration);
}

inline bool operator<(const UrlInfo& left, const UrlInfo& right)
{
	return AsTuple(left) < AsTuple(right);
}

inline bool IsExpired(const UrlInfo& url)
{
	return (url.Expiration > std::chrono::system_clock::now());
}

struct ExpiredUrl
{
	std::chrono::system_clock::duration HowLong;
};
struct BadUrl {};

