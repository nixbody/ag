#pragma once

#include "color.h"
#include "font.h"
#include "insets.h"
#include "prop.h"

namespace ag
{
	/* Components' theme. */
	struct component_theme
	{
		/* Default constructor. */
		component_theme() = default;

		/* Copy constructor. */
		component_theme(const component_theme &) = default;

		/* Move constructor. */
		component_theme(component_theme &&) = default;

		/* Destructor. */
		virtual ~component_theme() noexcept = default;

		/* Copy-assignment operator. */
		component_theme &operator=(const component_theme &) = default;

		/* Move-assignment operator. */
		component_theme &operator=(component_theme &&) = default;

		/* Background color. */
		prop<color> bg_color;

		/* Text font. */
		prop<font> text_font;

		/* Text color. */
		prop<color> text_color;

		/* Line height. */
		prop<float> line_height;

		/* Button radius. */
		prop<float> button_radius;

		/* Button padding. */
		prop<insets> button_padding;

		/* Button font. */
		prop<font> button_font;

		/* Button primary color. */
		prop<color> button_primary_color;

		/* Button secondary color. */
		prop<color> button_secondary_color;
	};
}
