#include "../../component.h"

#include <allegro5/allegro_primitives.h>

namespace ag
{
	void component::draw() const
	{
		const auto &s = style();
		if (!s.visible()) return;

		const auto x = s.x(), y = s.y(), w = s.width(), h = s.height(), r = s.radius();
		const auto bc = s.bg_color();
		const auto b = s.border();

		if (b.color.a > 0 && b.thickness > 0) {
			al_draw_rounded_rectangle(
				x + (b.thickness * 0.5f),
				y + (b.thickness * 0.5f),
				x + w - (b.thickness * 0.5f),
				y + h - (b.thickness * 0.5f),
				r,
				r,
				al_map_rgba(b.color.r, b.color.g, b.color.b, b.color.a),
				b.thickness
			);
		}

		if (bc.a > 0) {
			al_draw_filled_rounded_rectangle(
				x + b.thickness,
				y + b.thickness,
				x + w - b.thickness,
				y + h - b.thickness,
				r,
				r,
				al_map_rgba(bc.r, bc.g, bc.b, bc.a)
			);
		}
	}

	const std::optional<component::parent_ref> &component::parent() const
	{
		return parent_;
	}

	float component::width() const
	{
		return style().width();
	}

	float component::height() const
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
