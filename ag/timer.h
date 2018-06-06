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
		template <typename Rep, typename Period = std::chrono::duration<Rep>::period>
		using duration = std::chrono::duration<Rep, Period>;

		/* Get timer with the given native handle. */
		static timer &get(const std::any &native_timer_handle);

		/* Signal which is emitted when this timer ticked. */
		signal<const events::timer_ticked &> on_ticked;

		/* Create a new timer registered with the given event queue. */
		template <typename Rep, typename Period>
		constexpr timer(const duration<Rep, Period> &tick_interval, event_queue &queue = default_event_queue()):
			timer{duration<double>{tick_interval}.count(), queue}
		{}

		/* Create a new timer registered with the given event queue. */
		timer(double tick_interval, event_queue &queue = default_event_queue());

		/* Disable copying. */
		timer(const timer &) = delete;

		/* Disable moving. */
		timer(timer &&) = delete;

		/* Destroy this timer and unregister it from its event queue. */
		~timer() noexcept;

		/* Disable copy-assignment. */
		timer &operator=(const timer &) = delete;

		/* Disable move-assignment. */
		timer &operator=(timer &&) = delete;

	private:
		/* Collection of all currently existing timers. */
		static std::unordered_map<void *, timer &> timers_;

		/* Native underlaying (implmentation specific) timer handle. */
		const std::any native_handle_;
	};
}
