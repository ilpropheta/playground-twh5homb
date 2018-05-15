# Invalid urls

Mark from our IT Security Department is worried because our service does not complain if an invalid url is passed to `ClickUrl`. You need to handle errors, somehow.

In C++ there are so many ways to manage errors that it's very hard to state which is better. As always, each comes with tradeoffs, pros and cons. Traditional ways are:

* exceptions
* error codes
* bool flags
* error listeners/receivers (similar to visitors)

C++17 comes with another way to handle such 

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