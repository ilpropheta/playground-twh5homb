#include "Catch.h"
#include "DbIdGenerator.h"
#include "MicroUrlService.h"

TEST_CASE("Make Micro Url", "We check if http://google.com is https://micro.url/bM [MakeUrl]",)
{
	MicroUrlService service(new DbIdGenerator());
	auto microUrl = service.MakeMicroUrl("http://google.com");
	REQUIRE(microUrl == "https://micro.url/bM");
}