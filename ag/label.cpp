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

	void label::draw()
	{
		component::draw();
		const auto &s = style();
		s.text_font().draw_text(text_, s.x(), s.y(), s.width(), s.text_color(), s.line_height(), s.text_align());
	}
}
