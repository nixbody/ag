#pragma once

#include "event_queue.h"
#include "events/timer.h"
#include "signal.h"

#include <any>
#include <chrono>
#include <unordered_map>

namespace ag
{
	using namespace std::chrono_literals;

	/* Timer ticking at constant rate. */
	class timer final
	{
	public:
		using key_type = void *;

		/* Get timer with the given native handle. */
		static timer &get(const std::any &native_timer_handle);

		/* Signal which is emitted when this timer ticked. */
		const signal<const events::timer_ticked &> on_ticked;

		/* Create a new timer registered with the given event queue. */
		template <typename Rep, typename Period>
		timer(const std::chrono::duration<Rep, Period> &tick_interval, const event_queue &queue = default_event_queue());

		/* Create a new timer registered with the given event queue. */
		timer(double tick_interval, const event_queue &queue = default_event_queue());

		/* Destroy this timer and unregister it from its event queue. */
		~timer();

	private:
		/* Collection of all currently existing timers. */
		static std::unordered_map<key_type, timer &> timers_;

		/* Native underlaying (implmentation specific) timer. */
		const std::any &native_handle_;
	};

	template <typename Rep, typename Period>
	timer::timer(const std::chrono::duration<Rep, Period> &tick_interval, const event_queue &queue):
		timer{std::chrono::duration<double>{tick_interval}.count(), queue}
	{}
}
