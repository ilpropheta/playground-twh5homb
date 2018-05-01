# A bit of modern C++ refactoring

## Welcome!

Welcome to my first interactive workshop! We'll put our hands on some modern C++ features by refactoring some code, thanks to [tech.io](https://tech.io).

Everything is self-contained and embedded in this playground. In case you feel like having a look at the full repo, [check it out](https://github.com/ilpropheta).

## MicroUrl, an url shortener toy project

Imagine your company has just acquired **MicroUrl** a revolutionary url shortner service. Your CIO has great plans for the future of **MicroUrl** but the codebase seems a bit old-fashioned and before digging into new development he wants you to modernize it a bit. Then, along the way, he will ask you to develop some improvements.

# Getting familiar with the environment

This first excercise is just to stretch your hands and let you explore the environment.

## Structure of the project

## Hands on!

**MicroUrl** is quite old and it gets back plain HTTP urls. Fix the function formatting urls in order to return HTTP**S** urls.

Put your hands on the code! Here you can see a few files from our codebase and a simple test that we'll run as soon as you push "Run":

@[Fix MicroUrlService.cpp]({"stubs": ["microurl/src/ver1/MicroUrlService.cpp", "microurl/src/ver1/MicroUrlService.h", "microurl/src/ver1/tests/NiceToMeetYou.cpp"],"command": "sh /project/target/run_test.sh ver1"})