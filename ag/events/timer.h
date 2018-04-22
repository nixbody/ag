#pragma once

#include <cstdint>

namespace ag { class timer; }
namespace ag::events
{
	/* Triggered when a timer ticked. */
	struct timer_ticked final
	{
		/* How many times source timer ticked so far. */
		const std::int64_t count;

		/* Source timer. */
		timer &source;
	};
}
