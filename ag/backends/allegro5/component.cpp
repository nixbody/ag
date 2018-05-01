#include "../../component.h"

#include <allegro5/allegro_primitives.h>

namespace ag
{
	void component::draw_border() const
	{
		const auto b{border()};

		if (!b.color.a || !b.thickness) return;

		const auto x{this->x()}, y{this->y()}, r{radius()};
		al_draw_rounded_rectangle(
			x + 0.5f * b.thickness,
			y + 0.5f * b.thickness,
			x + width() - 0.5f * b.thickness,
			y + height() - 0.5f * b.thickness,
			r,
			r,
			al_map_rgba(b.color.r, b.color.g, b.color.b, b.color.a),
			b.thickness
		);
	}

	void component::draw_background() const
	{
		const auto bc{bg_color()};

		if (!bc.a) return;

		const auto x{this->x()}, y{this->y()}, r{radius()};
		const auto b{border()};
		al_draw_filled_rounded_rectangle(
			x + b.thickness,
			y + b.thickness,
			x + width() - b.thickness,
			y + height() - b.thickness,
			r,
			r,
			al_map_rgba(bc.r, bc.g, bc.b, bc.a)
		);
	}

	void component::draw_content() const
	{
		if (!text || !text().size()) return;

		const auto p{padding()};
		const auto b{border()};
		auto x{this->x() + p.left + b.thickness}, w{width() - p.left - p.right - 2.0f * b.thickness};

		const auto a{text_align()};
		switch (a) {
			case font::alignment::center: x += 0.5f * w; break;
			case font::alignment::right: x += w; break;
		}

		font().draw_text(text(), x, y() + p.top + b.thickness, w, text_color(), line_height(), a);
	}
}
