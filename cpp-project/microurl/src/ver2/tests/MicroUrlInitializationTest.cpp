#include "3rdparty/Catch.h"
#include "ver1/DbIdGenerator.h"
#include "ver1/MicroUrlService.h"

TEST_CASE("Initialization Test", "Can you make this compile? [MakeUrl]",)
{
	MicroUrlService service(std::make_unique<DbIdGenerator>());
	auto microUrl = service.MakeMicroUrl("http://google.com");
	REQUIRE(microUrl == "https://micro.url/bM");
}