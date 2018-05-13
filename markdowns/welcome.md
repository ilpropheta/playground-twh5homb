# A bit of post-modern C++ refactoring

## Welcome!

Welcome to my first interactive workshop on [tech.io](https://tech.io)!

This playground serves as an interactive environment to people attending this workshop at the Italian C++ Meetup in Modena on June 14.

I'll show you some "must know" features and idioms of **post**-modern C++. I like calling this era of C++ development **post-** modern because the term "modern" was introduced more than 17 years ago in [Alexandrescu's book](https://en.wikipedia.org/wiki/Modern_C%2B%2B_Design).

Through these pages, you'll have the opportunity to put your hands on some code by refactoring a small existing codebase. The exercises are very simple and they are intended to let you play and go beyond the simple requests.

### Post-modern C++ programmers are like Bruce Lee

Bruce Lee used to say:

> The best fighter is someone who can adapt in any style

C++ has implemented this idea very well, because it's been independent from the paradigm since its birth.

After the revolution brought by C++11, other paradigms - like functional - became a bit simpler with C++11, and then people have started mixing styles more often than before.

Post-modern C++ programmers should master idioms from different paradigms and styles, and use them conveniently. 

## Playground structure

Everything is self-contained and embedded in this **playground**. Under the hood, this environment is generated from this [github repo](https://github.com/ilpropheta). Tech.io is really amazing!

Every section (page) of this playground points to a newer version of the C++ project under the hood. This way you never get behind. 
Basically, I have deployed incremental versions of the example codebase you'll work on and I set up as many executables as I needed, with **CMake**.

In addition, you can build the [full repo](https://github.com/ilpropheta) on your machine and play "offline".

## Tools

This workshop will show you some C++11, C++14 and C++17 features. For this reason you need a suitable compiler. I have tested the codebase with Visual Studio 2017 15.7. Online, the code will be compiled with **GCC 7.2**.

### Catch

Behind the scenes, this codebase has a few unit tests made with [Catch](https://github.com/catchorg/Catch2). In case a test fails you will se the full output.

## MicroUrl, an url shortener toy project

During this workshop you will dress the part of an enthusiastic C++ programmer working at **Gugol**, a software giant leading the industry.

**Gugol** has just acquired **MicroUrl** from **NevercroSoft**, a revolutionary url shortner service which will be the top product of **Gugol** in the next years.

The CIO has great plans but the codebase seems a bit old-fashioned and before digging into Quantum Computing Support and Blockchain protocols he wants you to modernize the code a bit.

# Getting familiar with the environment

This first excercise is just to stretch your hands and let you explore the environment.

## Hands on!

**MicroUrl** is quite old and it gets back plain HTTP urls. Your boss heard that Google Chrome will mark all HTTP sites as 'not secure' starting in July and he asked you to fix such problem.

Change the following function accordingly and make the test pass:

@[Fix MicroUrlService.cpp]({"stubs": ["microurl/src/ver1/MicroUrlService.cpp", "microurl/src/ver1/MicroUrlService.h", "microurl/src/ver1/tests/NiceToMeetYou.cpp"],"command": "sh /project/target/run_test.sh ver1"})