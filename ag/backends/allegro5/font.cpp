#include "../../font.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_ttf.h>
#include <map>

namespace ag
{
	font::font(const std::string &resource, const int size)
	{
		static std::map<std::pair<const std::string *const, const int>, const ALLEGRO_FONT *const> fonts;

		if (fonts.find({&resource, size}) == fonts.end()) {
			fonts.try_emplace(
				{&resource, size},
				al_load_ttf_font_f(al_open_memfile(const_cast<char *>(resource.data()), resource.size(), "r"), nullptr, size, 0)
			);
		}

		native_handle_ = fonts.at({&resource, size});
	}

	font::~font() = default;

	void font::draw_text(
		const std::string &text,
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

		al_draw_multiline_text(
			std::any_cast<const ALLEGRO_FONT *>(native_handle_),
			al_map_rgba(color.r, color.g, color.b, color.a),
			x,
			y,
			max_width,
			line_height,
			flags,
			text.c_str()
		);
	}
}
