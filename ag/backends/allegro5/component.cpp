#include "../../component.h"

#include <algorithm>
#include <allegro5/allegro_primitives.h>

namespace ag
{
	void component::draw() const
	{
		const auto w{width()}, h{height()};
		if (!visible() || w <= 0.0f || h <= 0.0f) return;

		const auto x{this->x()}, y{this->y()}, r{radius()};
		const auto b{border()};
		al_set_clipping_rectangle(x, y, w, h);
		draw_border(x, y, w, h, r, b);
		draw_background(x, y, w, h, r, b);
		al_set_clipping_rectangle(x + b.thickness, y + b.thickness, w - 2.0f * b.thickness, h - 2.0f * b.thickness);
		draw_content();
	}

	void component::draw_border(
		const float x, const float y, const float w, const float h, const float r, const ag::border &b) const
	{
		if (!b.color.a || !b.thickness) return;

		const auto x1{x + 0.5f * b.thickness};
		const auto y1{y + 0.5f * b.thickness};
		const auto x2{std::max(x1 + b.thickness, x1 + w - b.thickness)};
		const auto y2{std::max(y1 + b.thickness, y1 + h - b.thickness)};
		al_draw_rounded_rectangle(x1, y1, x2, y2, r, r, al_map_rgba(b.color.r, b.color.g, b.color.b, b.color.a), b.thickness);
	}

	void component::draw_background(
		const float x, const float y, const float w, const float h, const float r, const ag::border &b) const
	{
		const auto bc{bg_color()};
		if (!bc.a) return;

		const auto x1{x + b.thickness};
		const auto y1{y + b.thickness};
		const auto x2{std::max(x1, x1 + w - 2.0f * b.thickness)};
		const auto y2{std::max(y1, y1 + h - 2.0f * b.thickness)};
		al_draw_filled_rounded_rectangle(x1, y1, x2, y2, r, r, al_map_rgba(bc.r, bc.g, bc.b, bc.a));
	}
}
