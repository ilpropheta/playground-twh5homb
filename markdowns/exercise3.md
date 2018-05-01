# Structure binding and tuple tricks

## Structure Binding

## std::tie trick

## Hands on!

It's time to check the stats of a shortened url! Complete the test below by using structure binding:

@[Use structure bindings. operator< made easy with std::tie]({"stubs": [
	 "microurl/src/ver4/tests/UrlInfoTest.cpp",
	 "microurl/src/ver4/MicroUrlInfo.h",
	],
	"command": "sh /project/target/run_test.sh ver4 binding"})

Our clients start asking how to compare url information...are you able to fix this test by properly implementing `operator<`?

@[Use structure bindings. operator< made easy with std::tie]({"stubs": [
	"microurl/src/ver4/tests/UrlInfoCompareTest.cpp",
	"microurl/src/ver4/MicroUrlInfo.h",
	],
	"command": "sh /project/target/run_test.sh ver4 less"})
	
::: Do you really give up? :(

Using structure bindings on `UrlInfoTest.cpp`:

```cpp
{
	auto[original, micro, clicks] = service.Stats(microUrl.c_str());
	REQUIRE (original == urlToShorten);
	REQUIRE (micro == microUrl);
	REQUIRE (initStat == 0);
		
	REQUIRE (original == service.ClickUrl(microUrl.c_str()));
	REQUIRE (original == service.ClickUrl(microUrl.c_str()));
}
{
	auto[original, micro, clicks] = service.Stats(microUrl.c_str());
	auto[original, micro, clicks] = service.Stats(microUrl.c_str());
	REQUIRE (clicks == 2);
}
```

It's a pity we cannot just `std::ignore` a field, isn't it?

Implementing `operator<` in `MicroUrlInfo.h` by using `std::tie`:

```cpp
inline auto AsTuple(const UrlInfo& info)
{
	return std::tie(info.OriginalUrl, info.MicroUrl, info.Clicks);
}

inline bool operator<(const UrlInfo& left, const UrlInfo& right)
{
	return AsTuple(left) < AsTuple(right);
}
```
:::