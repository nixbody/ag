#include "../../display.h"
#include "../../theme.h"

#include <allegro5/allegro.h>
#include <string>

namespace ag
{
	display::display(const int width, const int height, const std::string_view title, event_queue &event_queue):
		native_handle_{[width, height, title] {
			al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_RESIZABLE);
			al_set_new_window_title(std::string{title}.c_str());
			return al_create_display(width, height);
		}()},
		event_queue_{event_queue},
		on_event_occured{event_queue_.on_event_occured([this](const auto &e) { handle_event(e); })}
	{
		al_register_event_source(
			std::any_cast<ALLEGRO_EVENT_QUEUE *>(event_queue_.native_handle_),
			al_get_display_event_source(std::any_cast<ALLEGRO_DISPLAY *>(native_handle_))
		);

		redraw_timer_.on_ticked([this](const auto &) { redraw(); });
	}

	display::~display()
	{
		event_queue_.on_event_occured.disconnect(on_event_occured);
		al_destroy_display(std::any_cast<ALLEGRO_DISPLAY *>(native_handle_));
	}

	int display::width() const
	{
		return al_get_display_width(std::any_cast<ALLEGRO_DISPLAY *>(native_handle_));
	}

	int display::height() const
	{
		return al_get_display_height(std::any_cast<ALLEGRO_DISPLAY *>(native_handle_));
	}

	display &display::set_min_size(const int width, const int height)
	{
		al_set_window_constraints(std::any_cast<ALLEGRO_DISPLAY *>(native_handle_), width, height, 0, 0);
		al_apply_window_constraints(std::any_cast<ALLEGRO_DISPLAY *>(native_handle_), true);
		return *this;
	}

	display &display::draw(box &scene)
	{
		scene_ = &scene;
		scene_->x = scene_->y = 0.0f;
		scene_->width = [this]() -> float { return width(); };
		scene_->height = [this]() -> float { return height(); };
		if (!scene_->line_height) scene_->line_height = [] { return get_theme().line_height(); };
		if (!scene_->font) scene_->font = [] { return get_theme().text_font(); };
		if (!scene_->text_color) scene_->text_color = [] { return get_theme().text_color(); };
		if (!scene_->text_align) scene_->text_align = font::alignment::left;

		focused_component_ = scene_;
		should_redraw_ = true;

		return *this;
	}

	display &display::redraw(const bool force)
	{
		if (!drawing_paused_ && (should_redraw_ || force)) {
			if (clear().scene_) scene_->draw();
			al_flip_display();
			should_redraw_ = false;
		}

		return *this;
	}

	display &display::clear()
	{
		const auto c{get_theme().bg_color()};
		al_reset_clipping_rectangle();
		al_clear_to_color(al_map_rgba(c.r, c.g, c.b, c.a));
		return *this;
	}

	void display::handle_event(const std::any &event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(event)};
		should_redraw_ = true;
		switch (e.type) {
			case ALLEGRO_EVENT_KEY_DOWN: handle_key_pressed(e); break;
			case ALLEGRO_EVENT_KEY_UP: handle_key_released(e); break;
			case ALLEGRO_EVENT_KEY_CHAR: handle_character_typed(e); break;
			case ALLEGRO_EVENT_MOUSE_AXES: handle_mouse_axes_changed(e); break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: handle_mouse_button_pressed(e); break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP: handle_mouse_clicked(e); break;
			case ALLEGRO_EVENT_TIMER: should_redraw_ = (&timer::get(e.timer.source) != &redraw_timer_); break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE: on_closed.emit(*this); break;
			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				al_acknowledge_resize(std::any_cast<ALLEGRO_DISPLAY *>(clear().native_handle_));
				on_resized.emit(*this);
				redraw(true);
				break;
			case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING:
				al_acknowledge_drawing_halt(std::any_cast<ALLEGRO_DISPLAY *>(pause_drawing().native_handle_));
				break;
			case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING:
				al_acknowledge_drawing_resume(std::any_cast<ALLEGRO_DISPLAY *>(resume_drawing().native_handle_));
				break;
		}
	}

	void display::handle_mouse_axes_changed(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).mouse};
		if (scene_ && e.display == std::any_cast<ALLEGRO_DISPLAY *>(native_handle_)) {
			auto &t{acquired_component_ ? *acquired_component_ : scene_->child_at_pos(e.x, e.y).value_or(*scene_).get()};
			if (&t != last_event_target_) {
				if (last_event_target_) last_event_target_
					->trigger(events::mouse_left{e.dx, e.dy, e.dz, e.dw, e.x, e.y, e.z, e.w, *last_event_target_});

				t.trigger(events::mouse_entered{e.dx, e.dy, e.dz, e.dw, e.x, e.y, e.z, e.w, t});
				last_event_target_ = &t;
			}
			t.trigger(events::mouse_axes_changed{e.dx, e.dy, e.dz, e.dw, e.x, e.y, e.z, e.w, t});
		}
	}

	void display::handle_mouse_button_pressed(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).mouse};
		if (scene_ && e.display == std::any_cast<ALLEGRO_DISPLAY *>(native_handle_)) {
			component &t = scene_->child_at_pos(e.x, e.y).value_or(*scene_);
			acquired_component_ = last_event_target_ = &t;
			focused_component_ = t.focusable() ? &t : nullptr;
			t.trigger(events::mouse_button_pressed{e.button, e.x, e.y, e.z, e.w, t});
		}
	}

	void display::handle_mouse_clicked(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).mouse};
		if (scene_ && e.display == std::any_cast<ALLEGRO_DISPLAY *>(native_handle_)) {
			auto &t{acquired_component_ ? *acquired_component_ : scene_->child_at_pos(e.x, e.y).value_or(*scene_).get()};
			acquired_component_ = nullptr;
			last_event_target_ = &t;
			t.trigger(events::mouse_clicked{e.button, e.x, e.y, e.z, e.w, t});
		}
	}

	void display::handle_key_pressed(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).keyboard};
		if (focused_component_ && e.display == std::any_cast<ALLEGRO_DISPLAY *>(native_handle_)) {
			focused_component_->trigger(events::key_pressed{e.keycode, *focused_component_});
		}
	}

	void display::handle_key_released(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).keyboard};
		if (focused_component_ && e.display == std::any_cast<ALLEGRO_DISPLAY *>(native_handle_)) {
			focused_component_->trigger(events::key_released{e.keycode, *focused_component_});
		}
	}

	void display::handle_character_typed(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).keyboard};
		if (focused_component_ && e.display == std::any_cast<ALLEGRO_DISPLAY *>(native_handle_)) {
			char chr[5];
			chr[al_utf8_encode(chr, e.unichar)] = '\0';
			focused_component_->trigger(events::character_typed{e.keycode, {chr, e.unichar}, *focused_component_});
		}
	}
}
