# Invalid urls

Currently, `ClickUrl` and `Stats` do not complain when receiving invalid urls. We can assume they have a precondition: only well-formed urls are admitted. That is, we can assume the input has always this form:

```
https://micro.url/SECRET
```

Suppose dispatching is done at a higher level and `ClickUrl` and `Stats` are only called when the url has this form.

On the other hand, only `MicroUrlService` is able to turn `SECRET` into an ID and then return the original associated url.

At the moment, `ClickUrl` and `Stats` do not complain if `SECRET` hides an unknown ID.

How to report such errors?

In C++ there are too many ways to manage errors that it's very hard to state which is better. As always, each comes with tradeoffs, pros and cons. Traditional ways include:

* exceptions
* error codes
* bool flags
* error listeners/receivers (similar to visitors)

Instead of analysing all the options above, I'd like to introduce you another way to handle failures you should know about.

## `optional<T>`

Being a hit for many years (in C++ - e.g. boost - and in other languages/paradigms), C++ has recently (C++17) welcomed `std::optional`, a value that may or may not be present. In other words, `optional` is like a "typed" box: it either contain or not contain a value `T`. We can ask the box if it contains an instance of `T` and, if so, we can retrieve it.

If an `optional<T>` contains a value, the value is **guaranteed to be allocated as part of the optional object footprint** (no dynamic memory allocation ever takes place).

`optional<T>` is a common construct in other languages (e.g. C# has `T?`, Haskell has `Maybe`, etc) so it's worth knowing it. Optional types come from functional programming and are *monads* (e.g. chainable).

A common use case for `optional` is the return value of a function that may fail. As opposed to other approaches, such as `std::pair<T,bool>`, `optional` handles expensive-to-construct objects well and is more readable, as the intent is expressed explicitly.

Another use case for `optional` is the *lazy construction* of objects. Other approaches, such as smart pointers, usually require dynamic allocation or being able to model a null state (like an empty string).

### Examples

Classical example:

```cpp
std::optional<int> try_parse_int(const std::string& s)
{
    //try to parse an int from the given string,
    //and return "nothing" if you fail
}
```

Optional arguments:

```cpp
std::vector<std::pair<std::string, double>> search(
    std::string query,
    std::optional<int> max_count,
    std::optional<double> min_match_score);
```

### Optional references

Does it `optional<T&>` make sense? It might, but it's not allowed in C++17.

Suppose we want to look up an entry into a certain data store:

```cpp
? find(const Key& key);
```

A good choice could be returning `std::optional<Value&>` to avoid copying `Value`, instead of using pointers (our intent would be much clearer). A commond workaround consists in using `reference_wrapper` we met some time ago:

```cpp
optional<reference_wrapper<Value>> find(const Key& key);
// or
optional<reference_wrapper<const Value>> find(const Key& key);
```

Continue Reading:

* [Clearer interfaces with `optional<T>`](https://www.fluentcpp.com/2016/11/24/clearer-interfaces-with-optionalt/)
* [Refactoring with C++17 `std::optional`](https://www.bfilipek.com/2018/04/refactoring-with-c17-stdoptional.html)
* [The Boost C++ Libraries: Boost.Optional](https://theboostcpplibraries.com/boost.optional)

## Hands on!

Mark, head of IT Security Department at **Gugol**, asked your team to make `ClickUrl` and `Stats` more defensive by handling unknown SECRETs.

Your team has discussed a bit and decided to handle failures with `optional`. The signatures have been already acommodated, complete the bodies and make the test pass:

@[Handling invalid urls with optional]({"stubs": [ 
	 "microurl/src/ver7/MicroUrlService.h",
	 "microurl/src/ver7/MicroUrlService.cpp",
	 "microurl/src/ver7/tests/UrlInfoTest.cpp",
	],
	"command": "sh /project/target/run_test.sh ver7 [optional]"})

## Bonus: `optional` chain

`optional` becomes much more powerful when it is used in **composition**, as its characteristics allow for pipelines to be created which don't need to explicitly handle errors at each step.

The simplest way to chain `optional` is defining an operator like:

```cpp
template<typename T, typename F>
auto operator||(std::optional<T> opt, F f)
{
	return opt ? f(opt.value()) : std::nullopt;
}
```

This enables chaining:

```cpp
auto value = 
    (Parse(formula)
    || Compile
    || Optimize
    || Evaluate).value_or(NAN);
```

Each stage of the pipeline is executed only if the previous has returned a good value (not `nullopt`) and has to return an instance of `optional`. The latter can be inconvenient:

```cpp
    return 
        Parse // return optional<string>
        || [](const string& s) { return s.substr(0, 3); } // suppose cannot fail
```

Instead, we have to write:

```cpp
    return 
        Parse
        || [](const string& s) { return optional<string>{s.substr(0, 3)}; } 
```

It's possible to tweak a bit `operator||` to make the first snippet work:

```cpp
template<typename T>
auto wrap(std::optional<T> opt)
{
	return opt;
}

template<typename T>
auto wrap(T value)
{
	return std::optional<T>(value);
}

template<typename T, typename F>
auto operator||(std::optional<T> opt, F f)
{
	return opt ? wrap(f, opt.value()) : std::nullopt;
}
```

Add chaining to your code above and adapt your functions.

## Bonus: syntactic sugar
	
An intern got excited about such monadic nature of `optional` but she would love passing member variables and functions, like in this snippet:
	
```cpp	
return 
	MakeUrlInfo // might return UrlInfo
	|| &UrlInfo::OriginalUrl; // <-- instead of [](const UrlInfo& url) { return url.OriginalUrl; };
}
```

Can you impress her by accommodating such request?

::: Do you really give up? :(

The trick consists in using `std::invoke`:

```cpp
template<typename T, typename F>
auto operator||(std::optional<T> opt, F f)
{
	return opt ? wrap(std::invoke(f, opt.value())) : std::nullopt;
}
```

`std::invoke` is a little gem from C++17 enabling generic invocation of callables. It works smoothly with member variables and functions too.
:::