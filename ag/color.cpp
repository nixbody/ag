#include "color.h"

namespace ag
{
	color::color(const uint32_t value):
		r((value & 0x00ff0000) >> 16),
		g((value & 0x0000ff00) >> 8),
		b((value & 0x000000ff)),
		a((value & 0xff000000) >> 24)
	{}

	color::color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a):
		r(r), g(g), b(b), a(a)
	{}
}
