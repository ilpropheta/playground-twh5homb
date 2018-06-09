# Structure bindings and tuple tricks

## `std::tuple`

A fixed-size collection of heterogeneous values. Basically, the vocabulary type for structured values.
 
```cpp
tuple<string, int, bool> nameAgeChecked = {"marco", 30, true};
```

tuples are powerful for giving the same generic interface to structured data. Sometimes you can just wrap data into tuples and operate on them in a uniform way.

## Structure Bindings

C++17 introduces the possibility to decompose tuple-like objects into **references** to their componenents:

```cpp
tuple<int, int, string> make();
auto [a, b, c] = make();

/* merely equivalent to:
auto __tmp = make();
auto& a = get<0>(__tmp);
auto& b = get<1>(__tmp);
auto& c = get<2>(__tmp);
*/
```

It works with **destructurable** types:

* tuple-like types
* arrays
* public data members

For instance:

```cpp
array<int, 2> arr = {1, 2};
auto [a, b] = arr;

/* merely equivalent to:
auto __tmp = arr;
auto& a = __tmp [0]; // get<0>(__tmp )
auto& b = __tmp [1]; // get<1>(__tmp )
*/
```

And:

```cpp
struct Rgb
{
    int r, g, b;
    float alpha;
};

Rgb rgb = ...;
auto [r, g, b, a] = rgb;
```

More specifically, a type is destructurable if:

* either all non-static data members: 
   * must be public
   * must be direct members of the type or members of the same public base class of the type
   * Cannot be anonymous unions
* or, it has: 
   * an `obj.get<>()` method or an ADL-able `get<>(obj)` overload
   * specializations of `std::tuple_size<>` and `std::tuple_element<>`

**Important detail**: The portion of the declaration preceding `[` applies to the hidden variable `e`, not to the introduced identifiers.

```cpp
int a = 1, b = 2;
const auto& [x, y] = std::tie(a, b); // x and y are of type int&
auto [z, w] = std::tie(a, b);        // z and w are still of type int&
assert(&z == &a);                    // passes
```

Continue Reading:

- [Reference](http://en.cppreference.com/w/cpp/language/structured_binding)
- [Adding C++17 structured bindings support to your classes](https://blog.tartanllama.xyz/structured-bindings/)

## `std::tie` idiom

We have met structured bindings and understood how it works, more or less. Before putting our hands on the code, let's meet another important tool of post-modern C++: `std::tie`.

`std::tie` is a function which creates a `std::tuple` of **references** to the parameters we pass it:

```cpp
tuple<int, int, int, float> ReadRGBA();

int r, g, b;
float a;
tie(r, g, b, a) = ReadRGBA(); // r, g, b, a are assigned
```

The example above is a compact way to assign multiple values from an expression. As you can imagine, this is really similar to structured bindings but it covers the case when we already have variables and we just want to assign them.

In addition, we can `std::ignore` uninteresting fields:

```cpp
int r, g, b;
tie(r, g, b, std::ignore) = ReadRGBA(); // I don't need alpha
```

In general, `std::tie` is useful when we need to create a *light* tuple on the fly and use tuple's capabilities. 

A common idiom consists in implementing **lexicographical comparison**:

```cpp
struct S 
{
    int n;
    std::string s;
    float d;
    
    bool operator<(const S& rhs) const
    {
        // compares n to rhs.n,
        // then s to rhs.s,
        // then d to rhs.d
        return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};
```

This very effective idiom could save time and make the code simpler. Try writing the same by hand and compare the result with the snippet above.

## Hands on!

Let's get familiar with these post-modern C++ concepts.

Your collegue Pete is obsessed with making tests clearer and more compact, and you have decided to support his cause by applying structured bindings to a working test.

You have a pending refactoring. It's time to get back and finish your work:

@[Use structure bindings]({"stubs": [
	 "microurl/src/ver4/tests/UrlInfoTest.cpp",
	 "microurl/src/ver4/MicroUrlInfo.h",
	 "microurl/src/ver4/MicroUrlService.h"
	],
	"command": "sh /project/target/run_test.sh ver4 [binding]"})

A very important client of our company is asking a new feature: she wants to sort shortened urls in some way. Can you implement a simple `operator<` for this purpose? 

@[operator< made easy with std::tie]({"stubs": [
	"microurl/src/ver4/tests/UrlInfoCompareTest.cpp",
	"microurl/src/ver4/MicroUrlInfo.h",
	],
	"command": "sh /project/target/run_test.sh ver4 [less]"})
	
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

Here is how to implement `operator<` by leveraging `std::tie`:

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