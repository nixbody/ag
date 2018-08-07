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

		/* Slider track color. */
		prop<color> slider_track_color;

		/* Slider progress color. */
		prop<color> slider_progress_color;

		/* Slider thumb color. */
		prop<color> slider_thumb_color;

		/* Slider track border. */
		prop<border> slider_track_border;

		/* Slider thumb border. */
		prop<border> slider_thumb_border;

		/* Slider track thickness. */
		prop<float> slider_track_thickness;

		/* Slider track radius. */
		prop<float> slider_track_radius;

		/* Slider thumb width. */
		prop<float> slider_thumb_width;

		/* Slider thumb height. */
		prop<float> slider_thumb_height;

		/* Slider thumb radius. */
		prop<float> slider_thumb_radius;

		/* Tells whether or not slider thumbs may overlap slider track. */
		prop<bool> slider_thumb_overlaps;
	};
}
