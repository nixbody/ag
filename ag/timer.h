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
		template <typename Rep, typename Period = typename std::chrono::duration<Rep>::period>
		using duration = std::chrono::duration<Rep, Period>;
		using seconds = std::chrono::duration<double>;

		/* Get timer with the given native handle. */
		static timer &get(const std::any &native_timer_handle);

		/* Signal which is emitted when this timer ticked. */
		signal<const events::timer_ticked &> on_ticked;

		/* Create a new timer registered with the given event queue. */
		template <typename Rep, typename Period>
		constexpr timer(
			const duration<Rep, Period> &tick_interval, bool started = true, event_queue &queue = default_event_queue()
		): timer{std::chrono::duration_cast<seconds>(tick_interval).count(), queue}
		{ if (started) start(); }

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

		/* Start this timer. */
		timer &start();

		/* Stop this timer. */
		timer &stop();

		/* Pause this timer. */
		timer &pause();

		/* Resume this timer. */
		timer &resume();

		/* Set tick interval of this timer. */
		template <typename Rep, typename Period>
		constexpr timer &set_tick_interval(const duration<Rep, Period> &interval)
		{ return set_tick_interval(std::chrono::duration_cast<seconds>(interval).count()); }

		/* Set tick interval of this timer. */
		timer &set_tick_interval(double interval);

		/* Get tick interval of this timer. */
		seconds tick_interval() const;

	private:
		/* Collection of all currently existing timers. */
		static std::unordered_map<void *, timer &> timers_;

		/* Native underlaying (implmentation specific) timer handle. */
		const std::any native_handle_;
	};
}
