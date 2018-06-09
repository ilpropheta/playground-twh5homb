# Use the Interfaces, Luke

C++ is a multi-paradigm programming language, supporting, among the others, the Object-Oriented paradigm.

**Interfaces** constitute a powerful basic concept of Object-Oriented Programming. They are, simply, a description of the actions that an object can do.

C++ does not really have a built-in support for interfaces like Java or C#. A way to declare an interface in C++ constists in declaring an abstract class with pure virtual functions:

```cpp
class Interface
{
public:
    virtual void func() = 0;
    //...
};
```

Actually, the canonical way to create an interface in C++ is to give it a **defaulted virtual destructor**:

```cpp
class Interface
{
public:
    virtual ~Interface() = default;
    virtual void func() = 0;
    //...
};
```

This can be avoided only if you are really sure that this class will never be deleted polymorphically. This is a polymorphic deletion:

```cpp
Interface* base = Factory::Create(); // will craft an instance of some concrete implementation
//...
delete base; // undefined behavior if Interface's destructor is not virtual
```

Many years ago, **Herb Sutter** elaborated a neat guideline:

> A base class destructor should be either public and virtual, or protected and nonvirtual.

Thus, we could have:

```cpp
class Interface
{
protected:
    ~Interface() = default;
public:    
    virtual void func() = 0;
    //...
};
```

This makes impossible to do such polymorphic deletion.

Anyway, the most common and flexible way to declare an interface in C++ consists in declaring a defaulted virtual destructor - unless you really cannot afford a virtual destructor:

```cpp
class Interface
{
public:
    virtual ~Interface() = default;
    virtual void func() = 0;
    //...
};
```

### `shared_ptr` does some magic

Imagine we decided to stay with the protected non-virtual destructor:

```cpp
class Animal
{
protected:
    ~Animal() = default;
public:    
    virtual void move() = 0;
    //...
};
```

Does the following code compile?

```cpp
shared_ptr<Animal> obj = Factory::CreateDog(); // get back shared_ptr<Dog>
```

Yes, because in this case `shared_ptr` knows that the actual object is of type `Dog`, then it knows how to delete it. `shared_ptr` dynamically creates a specific deleter for that purpose.

This is not the case for `unique_ptr`, that does not introduce such overhead.

### Enforce overriden functions with `override`

Since C++11, we can enforce that a derived class overrides a base function by using `override`:

```cpp
class Derived : public Interface
{
public:
    void func() override;
};
```

This is very expressive. For non-abstract class, this prevents errors like:

```cpp
class Base
{
public:
    virtual void func1();
    virtual void func2();
};

class Derived
{
public:
    void Func1(); // capital 'F'
};
```

The code compiled although `Derived` is not really overriding `Base::func1`. On the other hand:

```cpp
class Derived
{
public:
    void Func1() override;
};
```

This does not compile.

Use `override` as much as possible (many refactoring tools will automatically do).

## Hands on!

In the dusty corners of **MicroUrl**, you have found `IIdGenerator.h` that is probably an old attempt that a former developer did to extract the id generation concept into an interface.

It's time to fulfill such effort and complete the job!

You tasks:

- Make `DbIdGenerator` implement `IIdGenerator`
- Make `MicroUrlService` use `IIdGenerator`
- Make possible to pass to `MicroUrlService` a custom `IIdGenerator`

Lets' go:

@[Use the interface, Luke!]({"stubs": [
	 "microurl/src/ver3/DbIdGenerator.h",	 
	 "microurl/src/ver3/IIdGenerator.h",
	 "microurl/src/ver3/tests/MicroUrlCustomIdGeneratorTest.cpp",
	 "microurl/src/ver3/MicroUrlService.h",
	 "microurl/src/ver3/MicroUrlService.cpp",
	],
	"command": "sh /project/target/run_test.sh ver3"})