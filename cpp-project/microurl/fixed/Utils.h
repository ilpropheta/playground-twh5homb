#pragma once
#include <string>

namespace MicroUrl
{
	namespace Utils
	{		
		std::string idToShortURL(long int n);
		long int shortURLtoID(std::string shortURL);
	}
}