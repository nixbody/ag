#pragma once

#include "signal.h"

#include <any>
#include <functional>

namespace ag
{
	class display;

	/* Collects and stores events. */
	class event_queue final
	{
		friend display;

	public:
		/* Signal which is emitted when some event occurs. */
		const signal<std::any &&> on_event_occured;

		/* Initialize this queue. */
		event_queue();

		/* Tear down this queue. */
		~event_queue();

		/* Start waiting for events. */
		void wait_for_events() const;

		/* Run the given callable on the main/UI thread. */
		void run_later(std::function<void ()> runner) const;

	private:
		/* Native underlaying (implmentation specific) event queue. */
		std::any native_handle_;

		/* Native underlaying (implmentation specific) async event source. */
		std::any async_event_source_native_handle_;
	};

	/* Get the default event queue. */
	event_queue &default_event_queue();

	/* Run the given callable on the main/UI thread. */
	void run_later(std::function<void ()> runner, const event_queue &queue = default_event_queue());
}
