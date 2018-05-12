#pragma once

#include <type_traits>

namespace ag
{
	/* Enable a function if the given argument is invocable. */
	template <typename Invocable, typename ... T>
	using enable_if_invocable_t = std::enable_if_t<std::is_invocable_v<Invocable, T ...>>;

	/* Enable a function if the given argument is convertible to the given type. */
	template <typename From, typename To>
	using enable_if_convertible_t = std::enable_if_t<std::is_convertible_v<From, To>>;
}
