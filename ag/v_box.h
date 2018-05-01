#pragma once

#include "box.h"

namespace ag
{
	/* Vertical box. */
	class v_box : public box
	{
	public:
		/* Inherit box constructors. */
		using box::box;

	private:
		/* Get supposed Y coordinate of the given child. */
		float child_y(const component &child) const override;
	};
}
