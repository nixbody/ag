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
		connection operator ()(slot_type &&slot) const;

		/* Emit this signal. */
		void emit(T && ... args) const;

		/* Disconnect a slot from this signal. */
		void disconnect(const connection conn) const;

	private:
		/* List of slots connected to this signal. */
		mutable std::vector<slot_type> slots_;
	};

	template <typename ... T>
	typename signal<T ...>::connection signal<T ...>::operator ()(slot_type &&slot) const
	{
		slots_.push_back(std::move(slot));
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
