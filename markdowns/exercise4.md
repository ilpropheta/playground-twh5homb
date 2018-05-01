# Viewing strings

## `std::string_view` in a nutshell

Remember to say:

- null-termination is up to you (it's just a view)

## Hands on!

Our Chief Marketing Officer has just came back from CppCon where she attended a few talks about `std::string_view`. She is keen on selling to our investors that we are already using such new feature into our codebase.

All things considered, this request is not so crazy. We have a few places where `std::string_view` could be really helpful...

Work on `MicroUrlService` and replace `const char*` with `std::string_view` on its public functions. Decomment some lines in `StringViewTest.cpp` and make it work.

@[Replace const char* with std::string_view on our service's interface]({"stubs": [
	 "microurl/src/ver5/MicroUrlService.h",
	 "microurl/src/ver5/MicroUrlService.cpp",
	 "microurl/src/ver5/tests/StringViewTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver5 [stringview]"})
	
## Bonus Track: avoid temporary strings	in map lookups

IT is worried about our service getting to many requests per second and they decided to implement a very simple load balancing strategy to split the work among several instances of our service. We know it cannot scale but we decide to help optimize it a bit, in the meantime some people of our team will develop a better strategy.

The load balancing strategy is very naive. Basically, the job is sent to a certain instance of the service depending on the first letter of the url. Since IT people regularly attend [Coding Gym](http://coding-gym.org), they know this lookup can be implemented very easily byt using a `std::map`. The only problem is that their function is accepting `std::string_view` and so a conversion to `std::string` is made every time.

Can you help avoid such useless conversion? Accommodate `LoadBalancer` here below:

@[Replace const char* with std::string_view on our service's interface]({"stubs": [ 
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