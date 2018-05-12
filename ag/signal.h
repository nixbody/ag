#pragma once

#include "type_traits.h"

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
		struct connection final { const typename std::vector<slot_type>::size_type id; };

		/* Connect the given slot to this signal. */
		template <typename Slot, typename = enable_if_convertible_t<Slot, slot_type>>
		connection operator()(Slot &&slot)
		{ slots_.emplace_back(std::forward<Slot>(slot)); return {slots_.size() - 1}; }

		/* Emit this signal. */
		void emit(T && ... args) const
		{ for (const auto &slot : slots_) slot(std::forward<T>(args)...); }

		/* Disconnect a slot from this signal. */
		void disconnect(connection conn)
		{ slots_.erase(slots_.cbegin() + conn.id); }

	private:
		/* List of slots connected to this signal. */
		std::vector<slot_type> slots_;
	};
}
