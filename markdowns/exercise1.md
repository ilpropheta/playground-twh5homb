# Getting rid of new and delete

## Smart Pointers

### Hands on!

You've just learnt how good smart pointers are and you have found a good fit for them in **MicroUrl** codebase.

`MicroUrlService` is manually managing the lifetime of its `DbIdGenerator* m_idGenerator`. We have to replace it with `std::unique_ptr<IIdGenerator>`:

@[Refactor all these files to use unique_ptr]({"stubs": ["microurl/src/ver2/MicroUrlService.h", "microurl/src/ver2/MicroUrlService.cpp", "microurl/src/ver2/tests/MicroUrlInitializationTest.cpp"],"command": "sh /project/target/run_test.sh ver2"})

## Interfaces

### Hands on!

In the dusty corners of **MicroUrl**, we have found `IIdGenerator.h`, probably a first attempt that a former developer did to extract the id generation concept into an interface.

It's time to fulfill such effort and complete such job!

You tasks:

- Make `DbIdGenerator` implement `IIdGenerator`
- Make `MicroUrlService` use `IIdGenerator`
- Make possible to pass to `MicroUrlService` a custom `IIdGenerator`

Lets' go:

@[Make possible to pass a custom IdGenerator]({"stubs": [
	 "microurl/src/ver2/tests/MicroUrlCustomIdGeneratorInitializationTest.cpp", 
	 "microurl/src/ver2/DbIdGenerator.h", 
	 "microurl/src/ver2/IIdGenerator.h", 
	 "microurl/src/ver2/MicroUrlService.h", 
	 "microurl/src/ver2/MicroUrlService.cpp"
	],
	"command": "sh /project/target/run_test.sh ver2_2"})