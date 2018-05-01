# Getting rid of new and delete

## Smart Pointers

## Hands on!

You've just learnt how good smart pointers are and you have found a good fit in **MicroUrl** codebase.

`MicroUrlService` is manually managing the lifetime of its `IIdGenerator* m_idGenerator`. We have to replace it with `std::unique_ptr<IIdGenerator>`:

@[Refactor MicroUrlService.h and MicroUrlService.cpp]({"stubs": ["microurl/src/ver2/MicroUrlService.cpp", "microurl/src/ver2/MicroUrlService.h", "microurl/src/ver1/tests/MicroUrlInitializationTest.cpp"],"command": "sh /project/target/run_test.sh ver2"})