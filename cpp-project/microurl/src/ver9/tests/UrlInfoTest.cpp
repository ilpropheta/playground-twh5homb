// { autofold
#include "3rdparty/Catch.h"
#include "ver9/MicroUrlService.h"
#include <iostream>
// }

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