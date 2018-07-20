#pragma once

#include "animations/ripple.h"
#include "component.h"

namespace ag
{
	/* Button. */
	class button : public component
	{
	public:
		/* Button type. */
		enum class type {primary, secondary};

		/* Inherit component constructors. */
		using component::component;

		/* Type of this button. */
		prop<type> type{type::primary};

		/* Initialize a new button. */
		button()
		{
			width = [this] { return font().text_width(text()) + padding().left + padding().right + 2.0f * border().thickness; };
			height = [this] { return font().line_height() + padding().top + padding().bottom + 2.0f * border().thickness; };
			padding = [this] { return theme()->button_padding(); };
			border = [this] { return ag::border(type() == type::primary, {0, 0, 0, 30}); };
			radius = [this] { return theme()->button_radius(); };
			bg_color = [this] { return pick_color(type() == type::primary); };
			text_color = [this] { return pick_color(type() == type::secondary); };
			font = [this] { return theme()->button_font(); };
			text_align = font::alignment::center;
		}

	private:
		/* Background color stash. */
		prop<color> bg_color_;

		/* Ripple effect. */
		animations::ripple ripple_{*this};

		/* Pick primary or secondary color. */
		color pick_color(bool primary)
		{ return primary ? theme()->button_primary_color() : theme()->button_secondary_color(); }

		/* Will be called when the given event was triggered on this component. */
		void event_triggered(const events::mouse_entered &) override
		{ bg_color_ = bg_color; bg_color = bg_color_().darker(6.0); }

		/* Will be called when the given event was triggered on this component. */
		void event_triggered(const events::mouse_left &) override
		{ bg_color = bg_color_; }

		/* Will be called when the given event was triggered on this component. */
		void event_triggered(const events::mouse_button_pressed &event) override
		{ ripple_(float(event.x), float(event.y)); }
	};
}
