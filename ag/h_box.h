#pragma once

#include "box.h"

namespace ag
{
	/* Horizontal box. */
	class h_box : public box
	{
	private:
		/* Get supposed X coordinate of the given child. */
		float child_x(const component &child) const override;
	};
}
