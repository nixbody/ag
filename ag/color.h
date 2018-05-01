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
		constexpr color(uint32_t value) noexcept:
			r((value & 0x00ff0000u) >> 16u),
			g((value & 0x0000ff00u) >> 8u),
			b(value & 0x000000ffu),
			a((value & 0xff000000u) >> 24u ? (value & 0xff000000u) >> 24u : 255u)
		{}

		/* Create a new color. */
		constexpr color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255u) noexcept: r{r}, g{g}, b{b}, a{a}
		{}

		/* Compare this color to the given color. */
		constexpr bool operator==(const color &col) const noexcept
		{ return r == col.r && g == col.g && b == col.b && a == col.a; }

		/* Compare this color to the given color. */
		constexpr bool operator!=(const color &col) const noexcept
		{ return !operator==(col); }
	};
}
