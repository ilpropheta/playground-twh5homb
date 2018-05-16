# Invalid urls

Currently, `ClickUrl` and `Stats` do not complain when receiving invalid urls. We can assume they have a precondition: only well-formed urls are admitted. That is, we can assume the input has always this form:

```
https://micro.url/SECRET
```

Suppose dispatching is done at a higher level and `ClickUrl` and `Stats` are only called when the url has this form.

What about `SECRET`? Only `MicroUrlService` is able to validate such information and then proxy to the final expanded url.

At the moment, `ClickUrl` and `Stats` do not complain if `SECRET` is invalid.

In C++ there are so many ways to manage errors that it's very hard to state which is better. As always, each comes with tradeoffs, pros and cons. Traditional ways include:

* exceptions
* error codes
* bool flags
* error listeners/receivers (similar to visitors)

What else?

## `optional<T>`

After many years in the C++ ecosystem (e.g. boost) and in other paradigms/languages, C++ has welcomed `std::optional`, a value that may or may not be present. In other words, `optional` is like a "typed" box: it either contain or not contain a value `T`. We can ask the box if it contains an instance of `T` and, if so, we can retrieve it.

If an `optional<T>` contains a value, the value is **guaranteed to be allocated as part of the optional object footprint** (no dynamic memory allocation ever takes place).


## Hands on!

Mark from our IT Security Department is worried about such flaws and he has formally asked you to fix.

Your team has decided to handle possible failures by using `optional`. Complete the code and make the test pass:

@[Handling invalid urls with optional]({"stubs": [ 
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