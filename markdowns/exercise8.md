# Wrap up

![Congratulations!](https://upload.wikimedia.org/wikipedia/it/thumb/4/46/Dicapriogatsby.JPG/1200px-Dicapriogatsby.JPG)

You have done a great job! I hope you have enjoyed the workshop.

The best is yet to come: you should delve into the topics you liked the most and practice a bit more. Possibly, a second part of this workshop will follow up in a few months, including other interesting concepts and idioms of post-modern C++.

I don't know your C++ level, maybe the most part of this workshop has been easy for you, maybe the opposite.

> Only a sith lord deals in absolutes

After this workshop you might have new arrows available into your quiver. C++ does not have absolute rules though, we can just try narrowing down the range of alternatives with openness to new tools and with balancing compromises. As Bruce Lee used to say: *the best fighter is someone who can adapt on any style*, that we can reshape as *the best C++ programmer is someone who can adapt on any paradigm*.

We have met strong ideas that are likely always true and other concepts whose use needs thinking.

* **RAII** is probably the most important idiom in C++ and **smart pointers** are general-purpose tools implementing such idiom
   * the general rule is: don't let plain pointers own resources;
* **Interfaces** are powerful building block of object oriented programming. Although the support for interfaces in C++ is not explicit as in other languages, learn the idioms to build them correctly and safely. In addition, you can use smart pointers to effectively craft **factory functions**;
* **tuples** and **structure bindings** are useful to manipulate structured data with common functions and idioms. Along the way, you have learnt `std::tie might` idiom to easily and efficiently turn data into a "light" tuple (tuple of references);
* **string_view** is a powerful tool for **referencing** sequences of chars as `std::string`-like readonly objects;
* the introduction of **lambdas** revolutionized how we write code in C++, with the first effect of empowering the usage of STL algorithms ("no more excuses"). In addition, it opens to scenarios where functional programming could be a good fit. We cannot really speak of "functional programming" but it's a very good start;
* we have many ways and paradigms for handling errors in C++ (and, generally, in software). `std::optional` is a "monadic" way for encapsulating errors and missing values. It's a *vocabulary type*, meaning that it's the default way to express *nullable value semantics*.
 
See you next time!