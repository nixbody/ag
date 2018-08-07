#pragma once

#include "../component_theme.h"
#include "../resources.h"

namespace ag
{
	/* Material design inspired theme. */
	struct material_theme : component_theme
	{
		prop<color> primary_color{1, 135, 134}, secondary_color{255, 255, 255};

		material_theme()
		{
			bg_color = {[this] { return secondary_color(); }};
			text_font = {resources::roboto_regular_woff(), 18.0f};
			text_color = {0, 0, 0};
			line_height = 0.0f;
			button_radius = 4.0f;
			button_padding = {9.5f, 15.5f};
			button_font = {resources::roboto_medium_woff(), 18.0f};
			button_primary_color = {[this] { return primary_color(); }};
			button_secondary_color = {[this] { return secondary_color(); }};
			slider_track_color = {[this] { return primary_color().brighter(200.0); }};
			slider_progress_color = {[this] { return primary_color(); }};
			slider_thumb_color = {[this] { return primary_color(); }};
			slider_track_border = {0.0f, color{0, 0, 0}};
			slider_thumb_border = {0.0f, color{0, 0, 0}};
			slider_track_thickness = 2.0f;
			slider_track_radius = 0.0f;
			slider_thumb_width = 18.0f;
			slider_thumb_height = 18.0f;
			slider_thumb_radius = 9.0f;
			slider_thumb_overlaps = true;
		}
	};
}
