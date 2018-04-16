#pragma once

#include "box.h"

namespace ag
{
	/* Horizontal box. */
	class h_box : public box
	{
	public:
		/* Horizontal box style. */
		struct style_type : box::style_type
		{};

	protected:
		/* Get supposed X coordinate of the given child. */
		float child_x(const component &child) const override;
	};
}
