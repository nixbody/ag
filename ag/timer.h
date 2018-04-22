#pragma once

#include "event_queue.h"
#include "signal.h"

#include <any>
#include <chrono>
#include <cstdint>
#include <unordered_map>

namespace ag
{
	using namespace std::chrono_literals;

	/* Timer ticking at constant rate. */
	class timer final
	{
	public:
		using count_type = std::int64_t;
		using key_type = void *;

		/* Get timer with the given native handle. */
		static const timer &get(const std::any &native_timer_handle);

		/* Signal which is emitted when this timer ticked. */
		const signal<count_type> on_ticked;

		/* Create a new timer registered with the given event queue. */
		template <typename Rep, typename Period>
		timer(const std::chrono::duration<Rep, Period> &tick_interval, const event_queue &queue = default_event_queue());

		/* Create a new timer registered with the given event queue. */
		timer(const double tick_interval, const event_queue &queue = default_event_queue());

		/* Destroy this timer and unregister it from its event queue. */
		~timer();

	private:
		/* Collection of all currently existing timers. */
		static std::unordered_map<key_type, const timer &> timers_;

		/* Native underlaying (implmentation specific) timer. */
		const std::any &native_handle_;
	};

	template <typename Rep, typename Period>
	timer::timer(const std::chrono::duration<Rep, Period> &tick_interval, const event_queue &queue):
		timer{std::chrono::duration<double>{tick_interval}.count(), queue}
	{}
}
