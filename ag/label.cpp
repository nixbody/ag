#include "label.h"

namespace ag
{
	label::style_type &label::style()
	{
		return style_;
	}

	const label::style_type &label::style() const
	{
		return style_;
	}
}
