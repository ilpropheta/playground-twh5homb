#include "3rdparty/Catch.h"
#include "ver1/DbIdGenerator.h"
#include "ver1/MicroUrlService.h"

TEST_CASE("Initialization Test", "Can you turn DbIdGenerator* into a unique_ptr? [MakeUrl]",)
{
	MicroUrlService service(new DbIdGenerator>());
	auto microUrl = service.MakeMicroUrl("http://google.com");
	REQUIRE(microUrl == "https://micro.url/bM");
}