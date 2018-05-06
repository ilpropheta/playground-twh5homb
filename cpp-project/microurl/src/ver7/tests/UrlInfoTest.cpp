// { autofold
#include "3rdparty/Catch.h"
#include "ver7/MicroUrlService.h"
// }

TEST_CASE("Checking stats", "Let's adapt this test [optional]")
{	
	const auto urlToShorten = "http://italiancpp.org/win100million.believeme";
	MicroUrlService service;
	auto microUrl = service.MakeMicroUrl(urlToShorten);

	auto urlInfo = service.Stats(microUrl);
	REQUIRE (urlInfo != std::nullopt);
	REQUIRE (urlInfo->Clicks == 0);
	REQUIRE (urlInfo->OriginalUrl == urlToShorten);
	REQUIRE (urlInfo->MicroUrl == microUrl);

	REQUIRE (urlToShorten == *service.ClickUrl(microUrl.c_str()));
	REQUIRE (urlToShorten == *service.ClickUrl(microUrl.c_str()));
		
	urlInfo = service.Stats(microUrl);
	 REQUIRE(urlInfo->Clicks == 2);
}

TEST_CASE("Invalid urls", "Checking against invalid urls [optional]")
{
	MicroUrlService service;
	auto urlInfo = service.Stats("http://dontknow.com");
	REQUIRE(urlInfo == std::nullopt);

	auto originalUrl = service.ClickUrl("http://dontknow.com");
	REQUIRE(originalUrl == std::nullopt);
}