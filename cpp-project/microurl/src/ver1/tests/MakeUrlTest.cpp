#include "3rdparty/Catch.h"
#include "ver1/DbIdGenerator.h"
#include "ver1/MicroUrlService.h"

TEST_CASE("Make Micro Url", "We check if encoding http://google.com results in https://micro.url/bM [MakeUrl]",)
{
	MicroUrlService service(new DbIdGenerator());
	auto microUrl = service.MakeMicroUrl("http://google.com");
	REQUIRE(microUrl == "https://micro.url/bM");
}