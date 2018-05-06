# Invalid urls

## `optional<T>`

- alternative: codici errore, bool, eccezioni, visitor-style

## Hands on!

@[Use `optional` to handle invalid urls]({"stubs": [ 
	 "microurl/src/ver7/MicroUrlService.h",
	 "microurl/src/ver7/MicroUrlService.cpp",
	 "microurl/src/ver7/tests/UrlInfoTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver7 [optional]"})

	
## Bonus: chaining `optional`

## Bonus: `std::invoke` finesse
	
An intern got excited about chaining `optional`, however she would love simplifying the code above this way:
	
```cpp	
std::optional<std::string> MicroUrlService::ClickUrl(std::string_view microUrl)
{
	return 
		TryLookup(m_idToUrl, microUrl, [](auto& url) { url.Clicks++; })
		|| &UrlInfo::OriginalUrl; // <-- instead of lambda
}
```

Can you slightly change `operator||` to accommodate such request?

::: Do you really give up? :(

The trick consists in using `std::invoke`:

```cpp
template<typename T, typename F>
auto operator||(std::optional<T> opt, F f)
{
	return opt ? wrap(std::invoke(f, opt.value())) : std::nullopt;
}
```
:::