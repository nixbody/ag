#pragma once

#include "component.h"

namespace ag
{
	/* Region. */
	struct region final
	{
		/* This region's coordinates and size. */
		const float x, y, width, height;

		/* Construct a new region based on the given coordinates and size. */
		region(float x, float y, float width, float height): x{x}, y{y}, width{width}, height{height}
		{}

		/* Construct a new region based on the given component. */
		region(const component &c): x{c.x()}, y{c.y()}, width{c.width()}, height{c.height()}
		{}

		/* Tell whether or not this region contains the given coordinates. */
		constexpr bool contains(float x, float y) const
		{ return x >= this->x && x < this->x + width && y >= this->y && y < this->y + height; }
	};
}
