// { autofold
#include "3rdparty/Catch.h"
#include "ver6/MicroUrlService.h"
// }

TEST_CASE("Check service visit of stored urls work", "Implement MicroUrlService::Visit")
{	
	MicroUrlService service;
	
	std::vector<std::string> urls{ 
		"http://google.com", 
		"http://italiancpp.org", 
		"http://coding-gym.org" };
	
	std::vector<std::string> shortened(urls.size());
	transform(begin(urls), end(urls), begin(shortened), [&](auto& url) {
		return service.MakeMicroUrl(url);
	});
	
	auto i = 0;
	service.VisitMicroUrls([&](auto& url) {
		REQUIRE(url.MicroUrl == shortened[i]);
		REQUIRE(url.OriginalUrl == urls[i++]);
	});
	REQUIRE(i == 3);
}