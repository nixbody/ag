#pragma once

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
		using connection = typename std::vector<slot_type>::size_type;

		/* Connect the given slot to this signal. */
		template <typename Slot>
		connection operator()(Slot &&slot) const;

		/* Emit this signal. */
		void emit(T && ... args) const;

		/* Disconnect a slot from this signal. */
		void disconnect(connection conn) const;

	private:
		/* List of slots connected to this signal. */
		mutable std::vector<slot_type> slots_;
	};

	template <typename ... T>
	template <typename Slot>
	typename signal<T ...>::connection signal<T ...>::operator()(Slot &&slot) const
	{
		slots_.emplace_back(std::forward<Slot>(slot));
		return slots_.size() - 1;
	}

	template <typename ... T>
	void signal<T ...>::emit(T && ... args) const
	{
		for (const auto &slot : slots_) {
			slot(std::forward<T>(args)...);
		}
	}

	template <typename ... T>
	void signal<T ...>::disconnect(const connection conn) const
	{
		slots_.erase(slots_.cbegin() + conn);
	}
}
