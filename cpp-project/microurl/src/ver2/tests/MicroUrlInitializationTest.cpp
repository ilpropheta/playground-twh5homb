// { autofold
#include "3rdparty/Catch.h"
#include "ver2/MicroUrlService.h"
// }

TEST_CASE("Initialization Test", "This should keep working")
{
	MicroUrlService service;
	auto microUrl = service.MakeMicroUrl("http://google.com");
	REQUIRE(microUrl == "https://micro.url/bM");
}