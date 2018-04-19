#pragma once

#include "component.h"
#include "theme.h"

namespace ag
{
	/* Button. */
	class button : public component
	{
	public:
		/* Inherit component constructors. */
		using component::component;

		/* Button style. */
		struct style_type : component::style_type
		{
			style_type()
			{
				padding = [] { return get_theme().button_padding(); };
				radius = [] { return get_theme().button_radius(); };
				bg_color = [] { return get_theme().button_primary_color(); };
				text_font = [] { return get_theme().button_font(); };
				text_color = [] { return get_theme().button_secondary_color(); };
				text_align = font::alignment::center;
			}
		};

		/* Move constructor. */
		button(button &&btn);

		/* Copy constructor. */
		button(const button &btn);

		/* Move assignment operator. */
		button &operator=(button &&btn);

		/* Copy assignment operator. */
		button &operator=(const button &btn);

		/* Get style of this button. */
		style_type &style() override;

		/* Get style of this button. */
		const style_type &style() const override;

	private:
		/* Style of this button. */
		style_type style_;

		/* Set up this button. */
		void set_up();
	};
}
