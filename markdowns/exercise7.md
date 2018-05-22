# Making URLs expire

A new requirement is coming from **Gugol**'s CEO: URLs expiration...let's acquire the basic knowledge to implement such new massive improvement.

## A bit of time handling with `std::chrono`

From [The C++ Standard Library - A Tutorial and Reference, 2nd Edition - by Nicolai Josuttis](http://www.cppstdlib.com/):

`std::chrono` is a precision-neutral library (coming from Boost) merged into C++11. It was designed to be able to deal with the fact that timers and clocks might be different on different operating systems and improve over time in precision. The goal was to provide a precision-neutral concept by separating duraton and point of time ("timepoint") from specific clocks. As a result, the core of the chrono library consists of the following types or concepts, which serve as abstract mechanisms to specify and deal with points in and durations of time:

* A **duration** of time is defined as a specific number of ticks over a time unit (e.g. "3 minutes" is "3 ticks of a minute").
* A **timepoint** is defined as combination of a duration and a beginning of time (*epoch*).
* The concept of a timepoint, however, is parametrized by a **clock**, which is the object that defines the epoch of a timepoint.

In other words, timepoint is defined as a duration before or after an epoch, which is defined by a clock.

Continue Reading:

* [Clocks and Timers chapter](http://www.informit.com/articles/article.aspx?p=1881386&seqNum=2) from The C++ Standard Library - A Tutorial and Reference, 2nd Edition - by Nicolai Josuttis
* [Boost.Chrono](https://theboostcpplibraries.com/boost.chrono)
* [std::chrono on the C++ Reference](http://en.cppreference.com/w/cpp/chrono)

### Examples

Simple durations:

```cpp
auto onDay = chrono::hours(24);
auto oneSecond = chrono::seconds(1);
assert(chrono::seconds(1) == chrono::milliseconds(1000));
```

Simple duration operations:

```cpp
auto now = chrono::system_clock::now(); // timepoint
auto oneHourAhead = now + chrono::hours(1); // still timepoint
assert(oneHourAhead > now);
auto oneSecond = chrono::seconds(1);
cout << chrono::microseconds(oneSecond).count(); // 1000000
```

In general, implicit conversions to a more precise unit type are always possible. However, conversions to a coarser unit type are not, because you might lose information. You can still explicitly force such a conversion with a `duration_cast`:

```cpp
chrono::seconds sec(55);
chrono::minutes m1 = sec; // error
chrono::minutes m2 = chrono::duration_cast<chrono::minutes>(sec); // ok (0 minutes, though)
```

Values are truncated, not rounded.

Trivial profiler:

```cpp
auto tic = chrono::system_clock::now();
// ... operation ...
auto toc = chrono::system_clock::now();
cout << chrono::duration_cast<chrono::milliseconds>(toc - tic).count(); // commit to specific duration
```

## Hands on!

Congratulations! Your boss was so impressed with your recent achievements that he has decided to nominate you the project leader of **MicroUrl**.

Great power comes with great responsibility, though.

You are requested to implement a new feature that our CEO is propagating as the feature of the year: URLs could expire after a certain amount of time (1 year, by default ).

Feature requests:

* `MicroUrlService::MakeMicroUrl` must take an url duration
  * such a requirement is not clear here: it could be a specific quantity (e.g. hours) or not. Up to you, balance compromises
* clicking an expired url should be forbidden
* the failing test should become green
* add an extra test, if possible
 
A developer on your team did some changes on the code already, however since you are the project leader, you are not required to keep them in.

@[Give urls an expiration date]({"stubs": [ 
	 "microurl/src/ver8/MicroUrlInfo.h",
	 "microurl/src/ver8/MicroUrlService.h",
	 "microurl/src/ver8/MicroUrlService.cpp",
	 "microurl/src/ver8/tests/UrlInfoTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver8"})
	
