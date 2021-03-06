#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace ag
{
	/* Dynamic property. */
	template <typename T>
	struct prop final : std::function<T ()>
	{
		using std::function<T ()>::function;

		/* Initialize this property with no value set. */
		prop() = default;

		/* Create a new value of the underlying type and forward the given arguments to its constructor. */
		template <typename ... Args>
		prop(Args && ... args): prop{[v = T(std::forward<Args>(args)...)] { return v; }}
		{}
	};

	/* Dynamic std::string_view property. */
	template <>
	struct prop<std::string_view> final : std::function<std::string_view ()>
	{
		using std::function<std::string_view ()>::function;

		/* Initialize this property with no value set. */
		prop() = default;

		/* Create a new value of the underlying type and forward the given arguments to its constructor. */
		template <typename ... Args>
		prop(Args && ... args): prop{[v = std::string{std::forward<Args>(args)...}]() -> std::string_view { return v; }}
		{}

		/* Create a new value from the given number. */
		template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		prop(T number): prop{[v = std::to_string(number)]() -> std::string_view { return v; }}
		{}
	};
}
