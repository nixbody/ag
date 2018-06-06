#pragma once

#include "type_traits.h"

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

namespace ag
{
	/* Signal. */
	template <typename ... T>
	class signal final
	{
	public:
		using slot_type = std::function<void (T ...)>;
		using connection = std::reference_wrapper<slot_type>;

		/* Connect the given slot to this signal. */
		template <typename Slot, typename = enable_if_convertible_t<Slot, slot_type>>
		connection operator()(Slot &&slot)
		{ slots_.emplace_back(std::forward<Slot>(slot)); return slots_.back(); }

		/* Emit this signal. */
		void emit(T && ... args) const
		{ for (const auto &slot : slots_) slot(std::forward<T>(args)...); }

		/* Disconnect the given slot from this signal. */
		void disconnect(connection conn)
		{
			const auto predicate{[conn](const auto &i) { return &i == &conn.get(); }};
			const auto it{std::find_if(slots_.cbegin(), slots_.cend(), predicate)};
			if (it != slots_.cend()) slots_.erase(it);
		}

	private:
		/* List of slots connected to this signal. */
		std::vector<slot_type> slots_;
	};
}
