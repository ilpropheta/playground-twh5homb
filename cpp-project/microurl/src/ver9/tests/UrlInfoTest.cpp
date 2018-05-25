// { autofold
#include "3rdparty/Catch.h"
#include "ver9/MicroUrlService.h"
#include <iostream>
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
	REQUIRE(service.Stats(oneDayLongMicroUrl)->Clicks == 1);

	service.ClickUrl(oneDayLongMicroUrl);
	REQUIRE(service.Stats(oneDayLongMicroUrl)->Clicks == 2);
}

TEST_CASE("Checking Click Url variant-style", "Let's use a std::variant to represent url access status")
{
	MicroUrlService service;
	auto micro = service.MakeMicroUrl("google.com", std::chrono::hours(1));
	
	service.ClickUrl(micro, [](auto status) {
		using T = decltype(status);

		if constexpr (std::is_same_v<T, BadUrl>)
		{
			std::cout << "This url is invalid\n";
		}
		else if constexpr (std::is_same_v<T, ExpiredUrl>)
		{
			std::cout << "This url is expired => " << std::chrono::duration_cast<std::chrono::minutes>(status.HowLong).count() << " minutes ago \n";
		}
		else 
		{
			std::cout << "This url points to => " << status.OriginalUrl << "\n";
		}
	});
}