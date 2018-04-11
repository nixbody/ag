#include "label.h"

namespace ag
{
	const std::string &label::text() const
	{
		return text_;
	}

	label::style_type &label::style()
	{
		return style_;
	}

	const label::style_type &label::style() const
	{
		return style_;
	}

	void label::draw() const
	{
		const auto &s = style();
		if (!s.visible()) return;

		component::draw();
		const auto p = s.padding();
		const auto b = s.border();
		float x = s.x() + p.left + b.thickness, w = s.width() - p.left - p.right - 2.0f * b.thickness;

		const auto a = s.text_align();
		switch (a) {
			case font::alignment::center: x += 0.5f * w; break;
			case font::alignment::right: x += w; break;
		}

		s.text_font().draw_text(text_, x, s.y() + p.top + b.thickness, w, s.text_color(), s.line_height(), a);
	}
}
