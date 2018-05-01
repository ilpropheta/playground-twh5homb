// { autofold
#include "3rdparty/Catch.h"
#include "ver4/MicroUrlService.h"
// }

TEST_CASE("Checking stats", "Let's use structure bindings [binding]")
{	
	const auto urlToShorten = "http://italiancpp.org/win100million.believeme";
	MicroUrlService service;
	auto microUrl = service.MakeMicroUrl(urlToShorten);
		
	// ... 
	//REQUIRE (original == urlToShorten);
	//REQUIRE (micro == microUrl);
	//REQUIRE (clicks == 0);
			
	//REQUIRE (original == service.ClickUrl(microUrl.c_str()));
	//REQUIRE (original == service.ClickUrl(microUrl.c_str()));
	
	// ...
	// REQUIRE (clicks == 2);
}

TEST_CASE("Comparing UrlInfo", "Can you write operator< for UrlInfo? [less]")
{
	{
		UrlInfo url1{ "http://google.com", "url1", 0 };
		UrlInfo url2{ "http://google.com", "url1", 0 };
		REQUIRE(!(url1 < url2));
	}

	{
		UrlInfo url1{ "http://google.com", "url1", 0 };
		UrlInfo url2{ "http://google.it", "url2", 0 };
		REQUIRE(url1 < url2);
	}
}