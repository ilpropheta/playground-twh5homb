#pragma once
#include <optional>
#include <functional>

// very simple, just to explain the concept
// (e.g. can be optimized to save temporaries)

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
	return opt ? wrap(std::invoke(f, opt.value())) : std::nullopt;
}

template<typename T, typename F>
auto operator||(std::optional<std::reference_wrapper<T>> optRef, F f)
{
	return optRef ? wrap(std::invoke(f, optRef->get())) : std::nullopt;
}