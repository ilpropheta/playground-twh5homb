#pragma once
#include <string>

struct UrlInfo // structure bindings per estrarre roba in uscita
{
	std::string OriginalUrl;
	std::string MicroUrl;
	int Clicks;

	// refactoring
	//std::chrono::time_point<std::chrono::system_clock> CreationDate;
	//std::chrono::time_point<std::chrono::system_clock> ExpirationDate;
	//
	//// refactoring
	//optional<long> Creator;
};