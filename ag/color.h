#pragma once

#include <cstdint>

namespace ag
{
	/* Color. */
	struct color final
	{
		/* Individual channels of this color. */
		const uint8_t r, g, b, a;

		/* Create a new color. */
		color(const uint32_t value);

		/* Create a new color. */
		color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);
	};
}
