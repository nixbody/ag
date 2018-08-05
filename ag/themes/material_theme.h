#pragma once

#include "../component_theme.h"
#include "../resources.h"

namespace ag
{
	/* Material design inspired theme. */
	struct material_theme : component_theme
	{
		material_theme()
		{
			bg_color = {255, 255, 255};
			text_font = {resources::roboto_regular_woff(), 18.0f};
			text_color = {0, 0, 0};
			line_height = 0.0f;
			button_radius = 4.0f;
			button_padding = {9.5f, 15.5f};
			button_font = {resources::roboto_medium_woff(), 18.0f};
			button_primary_color = {33, 150, 243};
			button_secondary_color = {255, 255, 255};
		}
	};
}
