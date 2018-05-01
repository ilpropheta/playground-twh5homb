#pragma once
#include <string>

namespace Ext
{
	namespace Shortener
	{		
		std::string idToShortURL(long int n);
		long int shortURLtoID(std::string shortURL);
	}
}