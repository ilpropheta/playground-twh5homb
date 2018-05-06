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

	
::: Do you really give up? :(



```cpp
template<typename Action>
void MicroUrlService::VisitMicroUrls(Action action) const
{
	for (auto&[id, url] : m_idToUrl)
		action(url);
}
```
:::