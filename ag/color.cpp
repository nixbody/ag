#include "color.h"

constexpr uint8_t alpha(const uint32_t value)
{
	const auto a = static_cast<uint8_t>((value & 0xff000000u) >> 24u);
	return a ? a : 255u;
}

namespace ag
{
	color::color(const uint32_t value):
		r{static_cast<uint8_t>((value & 0x00ff0000u) >> 16u)},
		g{static_cast<uint8_t>((value & 0x0000ff00u) >> 8u)},
		b{static_cast<uint8_t>((value & 0x000000ffu))},
		a{alpha(value)}
	{}

	color::color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a):
		r{r}, g{g}, b{b}, a{a}
	{}

	bool color::operator==(const color &col) const
	{
		return r == col.r && g == col.g && b == col.b && a == col.a;
	}

	bool color::operator!=(const color &col) const
	{
		return !operator==(col);
	}
}
