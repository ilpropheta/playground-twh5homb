// { autofold
#include "3rdparty/Catch.h"
#include "ver1/MicroUrlService.h"
// }

TEST_CASE("Very First Test", "It seems our service is getting back plain HTTP urls... [MakeUrl]",)
{
	MicroUrlService service;
	auto microUrl = service.MakeMicroUrl("http://google.com");
	REQUIRE(microUrl == "https://micro.url/bM");
}