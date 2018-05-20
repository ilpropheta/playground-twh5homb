# Handling different url access status

## `variant<T>`

- mostrare esempio morra cinese

## Hands on!

@[Use `optional` to handle invalid urls]({"stubs": [ 
	 "microurl/src/ver9/MicroUrlService.h",	 
	 "microurl/src/ver9/tests/UrlInfoTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver9"})

	
::: Do you really give up? :(


```cpp
template<typename T, typename F>
auto operator||(std::optional<T> opt, F f)
{
	return opt ? wrap(std::invoke(f, opt.value())) : std::nullopt;
}
```
:::