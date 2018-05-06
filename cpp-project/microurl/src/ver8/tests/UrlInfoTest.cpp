// { autofold
#include "3rdparty/Catch.h"
#include "ver8/MicroUrlService.h"
// }

TEST_CASE("Expired urls shouldn't be clickable", "When an url expires, MicroUrlService::ClickUrl should return nullopt")
{	
	const auto urlToShorten = "http://italiancpp.org/win100million.believeme";
	MicroUrlService service;
	auto alreadyExpiredMicroUrl = service.MakeMicroUrl(urlToShorten, -std::chrono::hours(1));
	auto original = service.ClickUrl(alreadyExpiredMicroUrl);
	REQUIRE(original == std::nullopt);

	auto oneDayLongMicroUrl = service.MakeMicroUrl(urlToShorten, std::chrono::hours(24));
	original = service.ClickUrl(oneDayLongMicroUrl);
	REQUIRE(original != std::nullopt);
}

TEST_CASE("Invalid urls", "Checking against invalid urls")
{
	MicroUrlService service;
	auto urlInfo = service.Stats("http://dontknow.com");
	REQUIRE(urlInfo == std::nullopt);

	auto original = service.ClickUrl("http://dontknow.com");
	REQUIRE(original == std::nullopt);
}