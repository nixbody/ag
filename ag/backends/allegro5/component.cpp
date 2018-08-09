#include "../../box.h"

#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <cmath>

namespace ag
{
	bool component::clip(const bool clip_border) const
	{
		auto x{this->x()}, y{this->y()}, w{width()}, h{height()};
		if (clip_border) {
			const auto bt{border().thickness};
			x += bt; y += bt; w -= 2.0f * bt; h -= 2.0f * bt;
		}
		if (parent_) {
			auto px{parent_->x()}, py{parent_->y()}, pw{parent_->width()}, ph{parent_->height()};
			if (clip_border) {
				const auto bt{parent_->border().thickness};
				px += bt; py += bt; pw -= 2.0f * bt; ph -= 2.0f * bt;
			}
			if (x + w < px || y + h < py || x > px + pw || y > py + ph) return false;
			if (x < px) { x = px; w -= px - x; }
			if (x + w > px + pw) w -= x + w - px - pw;
			if (y < py) { y = py; h -= py - y; }
			if (y + h > py + ph) h -= y + h - py - ph;
		}
		const auto sf{display_ ? display_->scale_factor() : 1.0f};
		al_set_clipping_rectangle(std::floor(x * sf), std::floor(y * sf), std::ceil(w * sf), std::ceil(h * sf));
		return true;
	}

	void component::draw() const
	{
		const auto w{width()}, h{height()};
		if (!visible() || w <= 0.0f || h <= 0.0f) return;

		const auto x{this->x()}, y{this->y()}, r{radius()};
		const auto b{border()};
		if (clip()) draw_border(x, y, w, h, r, b);
		if (clip(true)) { draw_background(x, y, w, h, r, b); draw_content(); }
		if (clip()) draw_overlay();
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

	void component::draw_overlay() const
	{
		const auto oc{overlay_color()};
		if (!oc.a) return;

		const auto r{overlay_radius()};
		const auto x1{overlay_x()}, y1{overlay_y()};
		const auto x2{std::max(x1, x1 + overlay_width())}, y2{std::max(y1, y1 + overlay_height())};
		al_draw_filled_rounded_rectangle(x1, y1, x2, y2, r, r, al_map_rgba(oc.r, oc.g, oc.b, oc.a));
	}
}
