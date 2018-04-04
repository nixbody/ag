#include "../../component.h"

#include <allegro5/allegro_primitives.h>

namespace ag
{
	void component::draw()
	{
		const auto &s = style();
		if (!s.visible()) return;

		const auto x = s.x(), y = s.y(), w = s.width(), h = s.height(), r = s.radius();
		const auto &bc = s.bg_color();
		const auto &b = s.border();

		if (b.thickness > 0) {
			al_draw_rounded_rectangle(
				x + (b.thickness * 0.5f),
				y + (b.thickness * 0.5f),
				w - (b.thickness * 0.5f),
				h - (b.thickness * 0.5f),
				r,
				r,
				al_map_rgba(b.color.r, b.color.g, b.color.b, b.color.a),
				b.thickness
			);
		}

		al_draw_filled_rounded_rectangle(
			x + b.thickness, y + b.thickness, w - b.thickness, h - b.thickness, r, r, al_map_rgba(bc.r, bc.g, bc.b, bc.a)
		);
	}

	const std::optional<component::parent_ref> &component::parent() const
	{
		return parent_;
	}

	float component::width()
	{
		return style().width();
	}

	float component::height()
	{
		return style().height();
	}

	component &component::hide()
	{
		style().visible = false;
		return *this;
	}

	component &component::show()
	{
		style().visible = true;
		return *this;
	}
}
