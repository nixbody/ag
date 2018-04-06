#include "../../font.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_ttf.h>
#include <map>
#include <utility>

namespace ag
{
	font::font(const std::string &resource, const int size)
	{
		static std::map<const std::string *, ALLEGRO_FILE *> files;
		static std::map<std::pair<const std::string *, const int>, const ALLEGRO_FONT *> fonts;

		if (files.find(&resource) == files.end()) {
			files.try_emplace(&resource, al_open_memfile(const_cast<char *>(resource.data()), resource.size(), "r"));
		}
		if (fonts.find({&resource, size}) == fonts.end()) {
			auto f = al_load_ttf_font_f(files.at(&resource), nullptr, size, 0);
			fonts.try_emplace({&resource, size}, f);
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
