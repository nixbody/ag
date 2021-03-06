#pragma once

#include "color.h"

namespace ag
{
	/* Component border. */
	struct border final
	{
		/* Thickness of this border. */
		const float thickness;

		/* Color of this border. */
		const color color;

		/* Create a new border. */
		constexpr border(float thickness, const ::ag::color &color) noexcept: thickness{thickness}, color{color}
		{}
	};
}
