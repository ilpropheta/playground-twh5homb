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
	"command": "sh /project/target/run_test.sh ver5"})
	
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
:::