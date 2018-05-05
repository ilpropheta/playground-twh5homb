// { autofold
#include "3rdparty/Catch.h"
#include "ver6/MicroUrlService.h"
#include <map>
#include <algorithm>
// }

struct CounterVisitor
{
	void operator()(const UrlInfo& info)
	{
		m_freq[info.OriginalUrl]++;
	}

	std::string MostPopular()
	{
		return 
			!m_freq.empty() 
			? std::max_element(begin(m_freq), end(m_freq), [](auto& left, auto& right) {
				return left.second < right.second;
			})->first
			: "";
	}

private:
	std::map<std::string, int> m_freq;
};

TEST_CASE("Using Visit to count the most popular urls", "Can you pass stateful visitors to VisitMicroUrls? [stateful]")
{	
	MicroUrlService service;
	
	for (auto i=0; i<5; ++i)
		service.MakeMicroUrl("http://google.com");
	for (auto i = 0; i<10; ++i)
		service.MakeMicroUrl("http://italiancpp.org");
	for (auto i = 0; i<8; ++i)
		service.MakeMicroUrl("http://coding-gym.org");


	CounterVisitor visitor;
	service.VisitMicroUrls(visitor);

	REQUIRE(visitor.MostPopular() == "http://italiancpp.org");
}