# Don't give your house keys to those pointers!

Pointers are cheap but at the same time very unclear. We cannot easily figure out what a pointer really is for any pieces of code:

```cpp
void Func(int* p)
```

What does `p` mean?

* should `Func` delete it?
* can it be null?
* single instance or array?
* out parameter?
 
Among the problems above, the most dangerous one is very likely on **ownership**. Pointers should never own resources, at least in business code (can be different in libraries or low-level code).

Let's see what alternative we have in C++.

## Getting a glimpse of smart pointers

**Smart pointers** are crucial to the **RAII** (*Resource Acquisition Is Initialization*) idiom. The main goal of this idiom is to ensure that resource acquisition occurs at the same time that the object is initialized, so that all resources for the object are created and made ready in one line of code. In practical terms, the main principle of RAII is to give ownership of any *heap-allocated* resource to a *stack-allocated* object whose destructor contains the code to delete or free the resource and also any associated cleanup code.

If you feel you need to use pointers (first consider if you really do), you would normally want to use a smart pointer as this can alleviate many of the problems with raw pointers, mainly forgetting to delete the object and leaking memory.

In addition, a smart pointer defines a clear **ownership policy** as to when the object is destroyed.

The C++ standard library provides 3 smart pointers:

* [`unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr)
* [`shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr)
* [`weak_ptr`](https://en.cppreference.com/w/cpp/memory/weak_ptr)
 
The simplest smart pointer that should be preferred by default is `unique_ptr`, defining a clear *unique* ownership policy that means: the resource will be only owned by that smart pointer:

```cpp
unique_ptr<Resource> handle = Acquire();
// use handle
// ...throw exception...
// released automatically at the end of the scope - although an exception has been thrown
```

The code above would have leaked with raw pointers.

`unique_ptr` can't be copied, since it models a unique ownership model:

```cpp
unique_ptr<Resource> handle = Acquire();
auto copied = handle; // does not compile
```

Instead, `unique_ptr` can **transfer** ownership by `std::`moving:

```cpp
unique_ptr<Resource> handle = Acquire();
// ...
auto newOwner = std::move(handle);
// handle wraps nullptr here
// newOwner owns the resource here
```

`shared_ptr` models a simultaneous (**shared**) ownership policy, meaning that a resource can have multiple owners. As long as an owner is alive, so is the resource:

```cpp
shared_ptr<Resource> owner1 = Acquire();
{
    auto owner2 = owner1;
    // 2 owners here
    {
        auto owner3 = owner2;
        // 3 owners here
    }
    // 2 owners here
}
// 1 owners here

// imagine  owner1 goes out of scope: the resource is finally released
```

`shared_ptr` works by *reference counting* active owners. This, clearly, introduces some overhead.

`weak_ptr` is a smart pointer that holds a non-owning (**weak**) reference to an object that is managed by `shared_ptr`. It must be converted to `shared_ptr` in order to access the referenced object.

`weak_ptr` models temporary ownership: when an object needs to be accessed only if it exists, and it may be deleted at any time by someone else, `weak_ptr` is used to track the object, and it is converted to `shared_ptr` to assume temporary ownership. If the original `shared_ptr` is destroyed at this time, the object's lifetime is extended until the temporary `shared_ptr` is destroyed as well.


### Hands on!

You've just learnt how good smart pointers are and you want to impress your boss by using them in **MicroUrl**.

It seems there is a really good fit for `unique_ptr`: `MicroUrlService` is manually managing `m_idGenerator`'s lifetime. You have to use `std::unique_ptr<IIdGenerator>` instead:

@[Replace manual resource managing with unique_ptr]({"stubs": ["microurl/src/ver2/MicroUrlService.h", "microurl/src/ver2/MicroUrlService.cpp", "microurl/src/ver2/tests/MicroUrlInitializationTest.cpp"],"command": "sh /project/target/run_test.sh ver2"})