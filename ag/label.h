#pragma once

#include "component.h"

namespace ag
{
	/* Text label. */
	class label : public component
	{
	public:
		/* Inherit component constructors. */
		using ag::component::component;

		/* Label style. */
		struct style_type : component::style_type
		{};

		/* Get style of this label. */
		style_type &style() override;

		/* Get style of this label. */
		const style_type &style() const override;

	private:
		/* Style of this label. */
		style_type style_;
	};
}
