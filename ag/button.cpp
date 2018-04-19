#include "button.h"

#include <utility>

namespace ag
{
	button::button(button &&btn): component{std::move(btn)}
	{
		set_up();
	}

	button::button(const button &btn): component{btn}
	{
		set_up();
	}

	button &button::operator=(button &&btn)
	{
		component::operator=(std::move(btn));
		set_up();
		return *this;
	}

	button &button::operator=(const button &btn)
	{
		component::operator=(btn);
		set_up();
		return *this;
	}

	button::style_type &button::style()
	{
		return style_;
	}

	const button::style_type &button::style() const
	{
		return style_;
	}

	void button::set_up()
	{
		style_.width = label_width() + 31.0f;
		style_.height = style_.text_font().line_height() + 19.0f;
	}
}
