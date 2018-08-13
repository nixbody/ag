#pragma once

#include "box.h"

namespace ag
{
	/* Vertical box. */
	class v_box : public box
	{
	private:
		/* Get supposed Y coordinate of the first child. */
		float first_child_y() const;

		/* Get supposed Y coordinate of the given child. */
		float child_y(const component &child) const override;
	};
}
