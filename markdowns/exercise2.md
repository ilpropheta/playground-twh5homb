# Use the Interfaces, Luke

## Hands on!

In the dusty corners of **MicroUrl**, we have found `IIdGenerator.h`, probably a first attempt that a former developer did to extract the id generation concept into an interface.

It's time to fulfill such effort and complete the job!

You tasks:

- Make `DbIdGenerator` implement `IIdGenerator`
- Make `MicroUrlService` use `IIdGenerator`
- Make possible to pass to `MicroUrlService` a custom `IIdGenerator`

Lets' go:

@[Use the interface, Luke!]({"stubs": [
	 "microurl/src/ver3/DbIdGenerator.h",	 
	 "microurl/src/ver3/IIdGenerator.h",
	 "microurl/src/ver3/tests/MicroUrlCustomIdGeneratorTest.cpp",
	 "microurl/src/ver3/MicroUrlService.h",
	 "microurl/src/ver3/MicroUrlService.cpp",
	],
	"command": "sh /project/target/run_test.sh ver3"})