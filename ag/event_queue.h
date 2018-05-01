#pragma once

#include "signal.h"

#include <any>
#include <functional>
#include <type_traits>
#include <utility>

namespace ag
{
	class display;
	class timer;

	/* Collects and stores events. */
	class event_queue final
	{
		friend display;
		friend timer;

	public:
		/* Signal which is emitted when some event occurs. */
		signal<const std::any &> on_event_occured;

		/* Initialize a new queue. */
		event_queue();

		/* Disable copying. */
		event_queue(const event_queue &) = delete;

		/* Allow moving. */
		event_queue(event_queue &&) = default;

		/* Tear down this queue. */
		~event_queue();

		/* Disable copy-assignment. */
		event_queue &operator=(const event_queue &) = delete;

		/* Enable move-assignment. */
		event_queue &operator=(event_queue &&) = default;

		/* Start waiting for events. */
		void wait_for_events() const;

		/* Run the given invokable object on the main/UI thread. */
		void run_later(std::function<void ()> runner) const;

	private:
		/* Native underlaying (implmentation specific) event queue. */
		const std::any native_handle_;

		/* Native underlaying (implmentation specific) async event source. */
		const std::any async_event_source_native_handle_;
	};

	/* Get the default event queue. */
	inline event_queue &default_event_queue()
	{ static event_queue queue; return queue; }

	/* Run the given invokable object on the main/UI thread. */
	template <typename Invokable, typename = std::enable_if_t<std::is_convertible_v<Invokable, std::function<void ()>>>>
	void run_later(Invokable &&runner, const event_queue &queue = default_event_queue())
	{ queue.run_later(std::forward<Invokable>(runner)); }
}
