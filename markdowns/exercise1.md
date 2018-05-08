# Getting rid of new and delete

## Smart Pointers



### Hands on!

You've just learnt how good smart pointers are and you want to impress your boss by using them in **MicroUrl**.

It seems there is a really good fit for `unique_ptr`: `MicroUrlService` is manually managing `m_idGenerator`'s lifetime. You have to use `std::unique_ptr<IIdGenerator>` instead:

@[Replace manual resource managing with unique_ptr]({"stubs": ["microurl/src/ver2/MicroUrlService.h", "microurl/src/ver2/MicroUrlService.cpp", "microurl/src/ver2/tests/MicroUrlInitializationTest.cpp"],"command": "sh /project/target/run_test.sh ver2"})