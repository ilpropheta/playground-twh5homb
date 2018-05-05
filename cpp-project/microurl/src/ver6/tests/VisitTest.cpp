// { autofold
#include "3rdparty/Catch.h"
#include "ver6/MicroUrlService.h"
// }

TEST_CASE("Check service visit of stored urls work", "Implement MicroUrlService::VisitMicroUrls [visit]")
{	
	MicroUrlService service;
	
	std::vector<std::string> urls{ 
		"http://google.com", 
		"http://italiancpp.org", 
		"http://coding-gym.org" };
	
	std::vector<std::pair<std::string, std::string>> expected;
	for (auto& url : urls)
		expected.emplace_back(url, service.MakeMicroUrl(url));
	
	// do you feel brave? Replace for with transform:
	/*transform(begin(urls), end(urls), begin(expected), [&](auto& url){
		// ... ?
	});*/
	
	std::vector<std::pair<std::string, std::string>> actual;
	service.VisitMicroUrls([&](auto& url) {
		actual.emplace_back(url.OriginalUrl, url.MicroUrl);
	});

	REQUIRE ( true == std::is_permutation(begin(expected), end(expected), begin(actual)));
}