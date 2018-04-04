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
		border(const float thickness = 0.0f, const ::ag::color color = ::ag::color{0, 0, 0, 0});
	};
}
