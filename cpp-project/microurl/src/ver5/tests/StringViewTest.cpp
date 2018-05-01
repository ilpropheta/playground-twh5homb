// { autofold
#include "3rdparty/Catch.h"
#include "ver5/MicroUrlService.h"
// }

TEST_CASE("Check service works with std::string_view", "Replace const char* with std::string_view on MicroUrlService's functions [stringview]")
{	
	const auto urlToShorten = "http://google.com";
	MicroUrlService service;
		
	// std::string_view shortenThis = "http://google.com";
	// REQUIRE(service.MakeMicroUrl(shortenThis) == "https://micro.url/bM");
	
	// std::string_view andThis = "http://italiancpp.org";
	// REQUIRE(service.MakeMicroUrl(andThis) == "https://micro.url/bN");
}