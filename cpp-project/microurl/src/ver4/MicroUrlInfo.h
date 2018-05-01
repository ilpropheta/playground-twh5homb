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

inline bool operator<(const UrlInfo& left, const UrlInfo& right)
{
	return false;
}