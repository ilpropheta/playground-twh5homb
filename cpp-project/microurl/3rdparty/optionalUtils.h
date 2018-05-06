#pragma once
#include <optional>

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
	return opt ? wrap(f(opt.value())) : std::nullopt;
}