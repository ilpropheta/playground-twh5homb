#include "3rdparty/Catch.h"
#include "ver2/MicroUrlService.h"
#include "ver2/IIdGenerator.h"

struct StubIdGenerator : IIdGenerator
{
	StubIdGenerator(long id)
		: m_id(id)
	{
		
	}
	
	long Generate(const char*)
	{
		return m_id;
	}
	
	long m_id;
};

TEST_CASE("Passing a Stub IdGenerator", "Make this work")
{
	//auto stub = make_unique<StubIdGenerator>(1);
	//MicroUrlService service(move(stub));
	//auto microUrl = service.MakeMicroUrl("http://google.com");
	//REQUIRE(microUrl == "https://micro.url/b"); // id '1' will be mapped to 'b'
}