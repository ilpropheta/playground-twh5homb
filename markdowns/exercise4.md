# Viewing strings

## `std::string_view` in a nutshell

`string_view` gives us the ability to refer to an existing string in a non-owning way.

An instance of the `string_view` class can be thought of as a "view" into an existing character buffer. Specifically, a `string_view` consists of only a pointer and a length, identifying a section of character data that is not owned by the `string_view` and cannot be modified by the view. Consequently, making a copy of a `string_view` is a shallow operation: no string data is copied.

`string_view` has implicit conversion constructors from both `const char*` and `const string&`, and since `string_view` doesn’t copy, there is no O(n) memory penalty for making a hidden copy. In the case where a `const string&` is passed, the constructor runs in O(1) time. In the case where a `const char*` is passed, the constructor invokes a `strlen()` automatically (or you can use the two-parameter `string_view` constructor).



Remember that `string_view` **is not necessarily NUL-terminated**.

Continue reading:

* [C++17 string_view](https://skebanga.github.io/string-view/)
* [string_view odi et amo](https://marcoarena.wordpress.com/2017/01/03/string_view-odi-et-amo/)
* [Tip of the Week #1: string_view](https://abseil.io/tips/1)

## Hands on!

Our Chief Marketing Officer has just came back from *CppCon* where she attended a few talks about `std::string_view`. She is keen on selling to our investors that we are already using such new feature into our codebase.

All things considered, this request is not so crazy. We have a few places where `std::string_view` could be really helpful...

Work on `MicroUrlService` and replace `const char*` with `std::string_view` on its public functions. Decomment some lines in `StringViewTest.cpp` and make it work.

@[Replace const char* with std::string_view on our service's interface]({"stubs": [
	 "microurl/src/ver5/MicroUrlService.h",
	 "microurl/src/ver5/MicroUrlService.cpp",
	 "microurl/src/ver5/tests/StringViewTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver5 [stringview]"})
	
## Bonus Track: avoid temporary strings	in map lookups

IT is worried about that our service is getting too many requests per second and they decided to implement a very simple load balancing strategy to split the work. We know it cannot scale but we decide to help optimize it a bit, in the meantime some people of our team will develop a better strategy.

The load balancing strategy is very naive. Basically, the job is sent to a certain instance of the service depending on the first letter of the url. Since IT people regularly attend [Coding Gym](http://coding-gym.org), they know this lookup can be implemented very easily with `std::map`. The only problem is that their function is accepting `std::string_view` and so a conversion to `std::string` is made every time a lookup is performed.

Can you help them avoid such useless conversion? Accommodate `LoadBalancer` here below:

@[Use a transparent comparator]({"stubs": [ 
	 "microurl/src/ver5/tests/LoadBalancerTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver5 [lb]"})
	
::: Do you really give up? :(

Using `std::string_view` is as easy as using `std::string`. For example:

```cpp
std::string MicroUrlService::ClickUrl(std::string_view microUrl)
{
	auto secret = microUrl.substr(microUrl.find_last_of('/') + 1);
	auto& url = m_idToUrl[Ext::Shortener::shortURLtoID(secret.data())];
	url.Clicks++;
	return url.OriginalUrl;
}

```

The idim to construct a `std::string` from `std::string_view` is simple:

```cpp
std::string_view strView = ...;
std::string str {strView.data(), strView.size()};
```
:::