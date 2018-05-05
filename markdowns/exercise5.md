# A functional touch

## Lambdas, lambdas everywhere



## Hands on!

@[Implement a visit function in our service]({"stubs": [ 
	 "microurl/src/ver6/MicroUrlService.h",
	 "microurl/src/ver6/tests/VisitTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver6 [visit]"})

## Bonus: passing stateful visitors

The functional touch you have added to our service has impressed many developers. One guy implemented a visitor to find the most popular url that our users feed MicroUrl with. Although the logic seems correct, the test he wrote is not passing.

Can you help him?

@[Fix the test]({"stubs": [ 
	 "microurl/src/ver6/MicroUrlService.h",
	 "microurl/src/ver6/tests/StatefulVisitTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver6 [stateful]"})
	
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