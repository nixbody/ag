#pragma once

#include "box.h"

namespace ag
{
	/* Vertical box. */
	class v_box : public box
	{
	public:
		/* Vertical box style. */
		struct style_type : box::style_type
		{};

	protected:
		/* Get supposed Y coordinate of the given child. */
		float child_y(const component &child) const override;
	};
}
