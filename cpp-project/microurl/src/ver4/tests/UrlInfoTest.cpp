// { autofold
#include "3rdparty/Catch.h"
#include "ver4/MicroUrlService.h"
// }

TEST_CASE("Checking stats", "Let's use structure bindings [binding]")
{	
	const auto urlToShorten = "http://italiancpp.org/win100million.believeme";
	MicroUrlService service;
	auto microUrl = service.MakeMicroUrl(urlToShorten);
		
	// ... 
	//REQUIRE (original == urlToShorten);
	//REQUIRE (micro == microUrl);
	//REQUIRE (clicks == 0);
			
	//REQUIRE (original == service.ClickUrl(microUrl.c_str()));
	//REQUIRE (original == service.ClickUrl(microUrl.c_str()));
	
	// ...
	// REQUIRE (clicks == 2);
}