#include <sstream>
#include <iostream>
#include <sstream>
#pragma warning (disable:4566)

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_NOSTDOUT
#define CATCH_CONFIG_RUNNER
#include "Catch.h"

#include "TechIoUtils.h"

static std::stringstream CatchOutStream;
static std::stringstream CatchErrStream;
static std::stringstream CatchLogStream;

std::ostream& Catch::cout()
{	
	return CatchOutStream;
}
std::ostream& Catch::cerr()
{
	return CatchErrStream;
}
std::ostream& Catch::clog()
{
	return CatchLogStream;
}

struct MyListener : Catch::TestEventListenerBase {

	using TestEventListenerBase::TestEventListenerBase; // inherit constructor

	virtual void testCaseEnded(Catch::TestCaseStats const& testCaseStats) override 
	{
		if (testCaseStats.totals.testCases.failed > 0)
			TechIo::Message("Hint 💡", testCaseStats.testInfo.description);
	}
};
CATCH_REGISTER_LISTENER(MyListener)

int main(int argc, char* argv[])
{
	int result = Catch::Session().run(argc, argv);
	
	if (result == 0)
	{
		TechIo::Message("Great 🌟", "All tests passed!");
		TechIo::Succeed();
	}
	else
	{
		TechIo::Message("Oops! 🐞", "Something went wrong...");
		TechIo::Message("Hint 💡", "");
		std::stringstream ss;
		ss << CatchOutStream.rdbuf();
		TechIo::Message("Tests log", ss.str());
		TechIo::Fail();
	}

	return result;
}