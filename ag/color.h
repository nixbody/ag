#pragma once

#include <cstdint>

namespace ag
{
	/* Color. */
	class color final
	{
	public:
		/* Individual channels of this color. */
		const uint8_t r, g, b, a;

		/* Create a new color. */
		color(uint32_t value);

		/* Create a new color. */
		color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

		/* Compare this color to the given color. */
		bool operator==(const color &col) const;

		/* Compare this color to the given color. */
		bool operator!=(const color &col) const;
	};
}
