# A functional touch

## Lambdas, lambdas everywhere



## Hands on!

@[Implement a visit function in our service]({"stubs": [ 
	 "microurl/src/ver6/tests/MicroUrlService.h",
	 "microurl/src/ver6/tests/VisitTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver6"})
	
::: Do you really give up? :(

Range-based for loop combined with structure bindings (what a pity, we cannot express that `id` is unused)...

```cpp
template<typename Action>
void MicroUrlService::VisitMicroUrls(Action action) const
{
	for (auto&[id, url] : m_idToUrl)
		action(url);
}
```
:::