# Getting rid of new and delete

## Smart Pointers

### Hands on!

You've just learnt how good smart pointers are and you have found a good fit for them in **MicroUrl** codebase.

`MicroUrlService` is manually managing the lifetime of its `DbIdGenerator* m_idGenerator`. We have to replace it with `std::unique_ptr<IIdGenerator>`:

@[Refactor all these files to use unique_ptr]({"stubs": ["microurl/src/ver2/MicroUrlService.h", "microurl/src/ver2/MicroUrlService.cpp", "microurl/src/ver2/tests/MicroUrlInitializationTest.cpp"],"command": "sh /project/target/run_test.sh ver2"})

## Interfaces

### Hands on!

In the dusty corners of **MicroUrl**, we have found `IIdGenerator.h`, probably a first attempt that a former developer did to extract the id generation concept into an interface.

It's time to fulfill such effort!

Refactor `MicroUrlService` and write a new constructor that gets a `unique_ptr<IIdGenerator>`.

Make `MicroUrlCustomIdGeneratorInitializationTest.cpp` work.

@[Refactor all these files to use unique_ptr]({"stubs": ["microurl/src/ver2/MicroUrlService.h", "microurl/src/ver2/MicroUrlService.cpp", "microurl/src/ver2/tests/MicroUrlCustomIdGeneratorInitializationTest.cpp"],"command": "sh /project/target/run_test.sh ver2_2"})