#include "../../font.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_ttf.h>
#include <cmath>
#include <map>

namespace ag
{
	float font::line_height() const
	{
		return al_get_font_line_height(get<const ALLEGRO_FONT *>());
	}

	float font::text_width(const std::string_view text) const
	{
		ALLEGRO_USTR_INFO info;
		return al_get_ustr_width(get<const ALLEGRO_FONT *>(), al_ref_buffer(&info, text.data(), text.size()));
	}

	void font::draw_text(
		const std::string_view text,
		const float x,
		const float y,
		const float max_width,
		const color &color,
		const float line_height,
		const font::alignment align
	) const
	{
		if (text.empty()) return;

		int flags{0};
		switch (align) {
			case alignment::left: flags = ALLEGRO_ALIGN_LEFT; break;
			case alignment::right: flags = ALLEGRO_ALIGN_RIGHT; break;
			case alignment::center: flags = ALLEGRO_ALIGN_CENTER; break;
		}

		ALLEGRO_TRANSFORM current_transformation{*al_get_current_transform()}, transformation;
		al_identity_transform(&transformation);
		al_use_transform(&transformation);

		const float scale_factor{current_transformation.m[0][0]};
		ALLEGRO_USTR_INFO info;
		al_draw_multiline_ustr(
			std::any_cast<const ALLEGRO_FONT *>(load(size_ * scale_factor)),
			al_map_rgba(color.r, color.g, color.b, color.a),
			std::round(x * scale_factor),
			std::round(y * scale_factor),
			max_width * scale_factor,
			line_height * scale_factor,
			flags,
			al_ref_buffer(&info, text.data(), text.size())
		);

		al_use_transform(&current_transformation);
	}

	std::any font::load(const float size) const
	{
		static std::map<std::pair<void *const, const int>, const ALLEGRO_FONT *const> fonts;

		const int font_size(size);
		if (fonts.find({resource_, font_size}) == fonts.end()) {
			fonts.try_emplace(
				{resource_, font_size},
				al_load_ttf_font_f(al_open_memfile(resource_, resource_size_, "r"), nullptr, -font_size, 0)
			);
		}

		return fonts.at({resource_, font_size});
	}
}
