// { autofold
#include "3rdparty/Catch.h"
#include <map>
#include <string_view>
#include <string>
// }

class LoadBalancer
{
public:
	LoadBalancer()
	{
		// { autofold
		PrefixToIp.try_emplace("http://a", "10.15.7.1");
		PrefixToIp.try_emplace("http://b", "10.15.7.2");
		PrefixToIp.try_emplace("http://c", "10.15.7.3");
		PrefixToIp.try_emplace("http://d", "10.15.7.4");
		PrefixToIp.try_emplace("http://e", "10.15.7.5");
		PrefixToIp.try_emplace("http://f", "10.15.7.6");
		// }
	}

	std::string_view MicroUrlServiceIpFor(std::string_view s)
	{
		//								 v-- can we avoid this?
		auto it = PrefixToIp.lower_bound({ s.data(), s.size() });
		return std::prev(it)->second;
	}
private:
	std::map<std::string, std::string> PrefixToIp;
};

TEST_CASE("Heterogeneous map lookup", "Can we avoid converting to std::string? [lb]")
{	
	LoadBalancer lb;
	REQUIRE(lb.MicroUrlServiceIpFor("http://ciao.com") == "10.15.7.3");
	REQUIRE(lb.MicroUrlServiceIpFor("http://abacadabra.org") == "10.15.7.1");
	REQUIRE(lb.MicroUrlServiceIpFor("http://italiancpp.org") == "10.15.7.6");
}