#include "../../component.h"

#include <allegro5/allegro_primitives.h>

namespace ag
{
	component::component(std::string &&label): label_{std::move(label)}
	{}

	component::component(const std::string &label): label_{label}
	{}

	void component::draw() const
	{
		if (hidden_) return;

		draw_border();
		draw_background();
		draw_label();
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

	bool component::hidden() const
	{
		return hidden_;
	}

	component &component::hide()
	{
		hidden_ = true;
		return *this;
	}

	component &component::show()
	{
		hidden_ = false;
		return *this;
	}

	component &component::set_label(std::string &&label)
	{
		label_ = std::move(label);
		return *this;
	}

	component &component::set_label(const std::string &label)
	{
		label_ = label;
		return *this;
	}

	const std::string &component::label() const
	{
		return label_;
	}

	float component::label_width() const
	{
		return style().text_font().text_width(label_);
	}

	void component::draw_border() const
	{
		const auto &s = style();
		const auto b = s.border();

		if (!b.color.a || !b.thickness) return;

		const auto x = s.x(), y = s.y(), r = s.radius();
		al_draw_rounded_rectangle(
			x + 0.5f * b.thickness,
			y + 0.5f * b.thickness,
			x + s.width() - 0.5f * b.thickness,
			y + s.height() - 0.5f * b.thickness,
			r,
			r,
			al_map_rgba(b.color.r, b.color.g, b.color.b, b.color.a),
			b.thickness
		);
	}

	void component::draw_background() const
	{
		const auto &s = style();
		const auto bc = s.bg_color();

		if (!bc.a) return;

		const auto x = s.x(), y = s.y(), r = s.radius();
		const auto b = s.border();
		al_draw_filled_rounded_rectangle(
			x + b.thickness,
			y + b.thickness,
			x + s.width() - b.thickness,
			y + s.height() - b.thickness,
			r,
			r,
			al_map_rgba(bc.r, bc.g, bc.b, bc.a)
		);
	}

	void component::draw_label() const
	{
		const auto &s = style();
		const auto p = s.padding();
		const auto b = s.border();
		float x = s.x() + p.left + b.thickness, w = s.width() - p.left - p.right - 2.0f * b.thickness;

		const auto a = s.text_align();
		switch (a) {
			case font::alignment::center: x += 0.5f * w; break;
			case font::alignment::right: x += w; break;
		}

		s.text_font().draw_text(label_, x, s.y() + p.top + b.thickness, w, s.text_color(), s.line_height(), a);
	}

	void component::trigger(const events::mouse_axes_changed &event)
	{
		on_mouse_axes_changed.emit(event);
	}

	void component::trigger(const events::mouse_entered &event)
	{
		on_mouse_entered.emit(event);
	}

	void component::trigger(const events::mouse_left &event)
	{
		on_mouse_left.emit(event);
	}

	void component::trigger(const events::mouse_button_pressed &event)
	{
		on_mouse_button_pressed.emit(event);
	}

	void component::trigger(const events::mouse_button_released &event)
	{
		on_mouse_button_released.emit(event);
	}

	void component::trigger(const events::mouse_clicked &event)
	{
		on_mouse_button_clicked.emit(event);
	}
}
