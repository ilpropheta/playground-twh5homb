#include "Shortener.h"
#include <algorithm>

std::string Ext::Shortener::idToShortURL(long int n)
{
	char map[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string shorturl;
	while (n)
	{
		shorturl.push_back(map[n % 62]);
		n = n / 62;
	}
	std::reverse(shorturl.begin(), shorturl.end());
	return shorturl;
}

long int Ext::Shortener::shortURLtoID(const char* shortURL)
{
	long int id = 0;
	for (int i = 0; i < std::char_traits<char>::length(shortURL) ; i++)
	{
		if ('a' <= shortURL[i] && shortURL[i] <= 'z')
			id = id * 62 + shortURL[i] - 'a';
		if ('A' <= shortURL[i] && shortURL[i] <= 'Z')
			id = id * 62 + shortURL[i] - 'A' + 26;
		if ('0' <= shortURL[i] && shortURL[i] <= '9')
			id = id * 62 + shortURL[i] - '0' + 52;
	}
	return id;
}
