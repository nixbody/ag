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
		float x;

		switch (s.text_align()) {
			case font::alignment::left: x = s.x(); break;
			case font::alignment::center: x = s.x() + s.width() / 2.0f; break;
			case font::alignment::right: x = s.x() + s.width(); break;
		}

		s.text_font().draw_text(text_, x, s.y(), s.width(), s.text_color(), s.line_height(), s.text_align());
	}
}
