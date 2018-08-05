#include "../../box.h"

#include <allegro5/allegro.h>
#include <string>

ALLEGRO_DISPLAY *create_display(int width, int height, std::string_view title, int flags);
ALLEGRO_MOUSE_EVENT mouse_event(const std::any &native_event, float scale_factor);
ALLEGRO_DISPLAY *event_target_display(const std::any &native_event);
float default_scale_factor();
int dpi();

namespace ag
{
	template <>
	ALLEGRO_DISPLAY *display::get()
	{
		if (!native_handle_.has_value()) {
			int flags{0};
			if (resizable_) flags |= ALLEGRO_RESIZABLE;
			if (fullscreen_) flags |= ALLEGRO_FULLSCREEN_WINDOW;
			if (maximized_) flags |= ALLEGRO_MAXIMIZED;
			if (frameless_) flags |= ALLEGRO_FRAMELESS;
			if (!scale_factor_) scale_factor_ = default_scale_factor();
			native_handle_ = create_display(width_ * scale_factor_, height_ * scale_factor_, title_, flags);
			al_register_event_source(
				std::any_cast<ALLEGRO_EVENT_QUEUE *>(event_queue_.native_handle_),
				al_get_display_event_source(std::any_cast<ALLEGRO_DISPLAY *>(native_handle_))
			);
			scale(scale_factor_).move(x_, y_);
		}
		return std::any_cast<ALLEGRO_DISPLAY *>(native_handle_);
	}

	display::display(const float width, const float height, const std::string_view title, event_queue &event_queue):
		width_{width},
		height_{height},
		title_{title},
		scene_{*(new box)},
		focused_component_{&scene_},
		event_queue_{event_queue},
		on_event_occured{event_queue_.on_event_occured([this](const auto &e) { handle_event(e); })}
	{
		scene_.set_display(*this);
		scene_.theme = [] { return component::default_theme; };
		scene_.x = scene_.y = 0.0f;
		scene_.width = [this] { return width_; };
		scene_.height = [this] { return height_; };
		scene_.line_height = [this] { return scene_.theme()->line_height(); };
		scene_.font = [this] { return scene_.theme()->text_font(); };
		scene_.text_color = [this] { return scene_.theme()->text_color(); };
		scene_.text_align = font::alignment::left;
		redraw_timer_.on_ticked([this](const auto &) { redraw(); redraw_timer_.stop(); });
	}

	display::~display()
	{
		event_queue_.on_event_occured.disconnect(on_event_occured);
		delete &hide().scene_;
	}

	display &display::set_min_size(const float width, const float height)
	{
		if (!hidden_) {
			auto handle{get<ALLEGRO_DISPLAY *>()};
			al_set_window_constraints(handle, width * scale_factor_, height * scale_factor_, 0, 0);
			al_apply_window_constraints(handle, true);
		}
		return *this;
	}

	display &display::resize(const float width, const float height)
	{
		width_ = width;
		height_ = height;
		if (!hidden_) {
			auto *const handle{get<ALLEGRO_DISPLAY *>()};
			al_resize_display(handle, width * scale_factor_, height * scale_factor_);
		}
		return redraw();
	}

	display &display::scale(const float factor, const bool resize_display)
	{
		scale_factor_ = factor;
		if (!hidden_) {
			ALLEGRO_TRANSFORM transformation;
			al_set_target_backbuffer(get<ALLEGRO_DISPLAY *>());
			al_identity_transform(&transformation);
			al_scale_transform(&transformation, factor, factor);
			al_use_transform(&transformation);
		}
		return (resize_display && !fullscreen_ && !maximized_) ? resize(width_, height_) : redraw();
	}

	display &display::center()
	{
		ALLEGRO_MONITOR_INFO monitor;
		if (al_get_monitor_info(0, &monitor)) {
			const int max_width{monitor.x2 - monitor.x1}, max_height{monitor.y2 - monitor.y1};
			if (!scale_factor_) scale_factor_ = default_scale_factor();
			return move(
				std::max(0.5f * ((max_width / scale_factor_) - width_), 0.0f),
				std::max(0.5f * ((max_height / scale_factor_) - height_), 0.0f)
			);
		}
		return *this;
	}

	display &display::center(display &parent)
	{
		if (!parent.scale_factor_) parent.scale_factor_ = default_scale_factor();
		if (!scale_factor_) scale_factor_ = default_scale_factor();
		parent.update_position();
		const auto factor{parent.scale_factor_ / scale_factor_};
		return move(
			std::max(factor * parent.x_ + 0.5f * (factor * parent.width_ - width_), 0.0f),
			std::max(factor * parent.y_ + 0.5f * (factor * parent.height_ - height_), 0.0f)
		);
	}

	display &display::move(const float x, const float y)
	{
		if (!hidden_ && !fullscreen_ && !maximized_) {
			al_set_window_position(get<ALLEGRO_DISPLAY *>(), x * scale_factor_, y * scale_factor_);
			update_position();
		} else {
			x_ = x;
			y_ = y;
		}
		return *this;
	}

	display &display::set_frameless(const bool frameless)
	{
		if (!hidden_) {
			auto *const handle{get<ALLEGRO_DISPLAY *>()};
			al_set_display_flag(handle, ALLEGRO_FRAMELESS, frameless);
			width_ = al_get_display_width(handle) / scale_factor_;
			height_ = al_get_display_height(handle) / scale_factor_;
			update_position();
		}
		frameless_ = frameless;
		return *this;
	}

	display &display::set_fullscreen(const bool fullscreen)
	{
		if (!hidden_) {
			auto *const handle{get<ALLEGRO_DISPLAY *>()};
			al_set_display_flag(handle, ALLEGRO_FULLSCREEN_WINDOW, fullscreen);
			al_set_display_flag(handle, ALLEGRO_MAXIMIZED, maximized_);
			width_ = al_get_display_width(handle) / scale_factor_;
			height_ = al_get_display_height(handle) / scale_factor_;
			update_position();
		}
		fullscreen_ = fullscreen;
		return *this;
	}

	display &display::set_maximized(const bool maximized)
	{
		if (!hidden_) {
			auto *const handle{get<ALLEGRO_DISPLAY *>()};
			al_set_display_flag(handle, ALLEGRO_FULLSCREEN_WINDOW, fullscreen_);
			al_set_display_flag(handle, ALLEGRO_MAXIMIZED, maximized);
			width_ = al_get_display_width(handle) / scale_factor_;
			height_ = al_get_display_height(handle) / scale_factor_;
			update_position();
		}
		maximized_ = maximized;
		return *this;
	}

	display &display::show()
	{
		hidden_ = false;
		return resume_drawing().redraw();
	}

	display &display::hide()
	{
		if (native_handle_.has_value()) {
			update_position();
			al_destroy_display(get<ALLEGRO_DISPLAY *>());
			native_handle_.reset();
		}
		pause_drawing().hidden_ = true;
		return *this;
	}

	display &display::redraw()
	{
		if (!hidden_ && !drawing_paused_) {
			clear().scene_.draw();
			al_flip_display();
		}
		return *this;
	}

	display &display::clear()
	{
		if (!hidden_ && !drawing_paused_) {
			const auto c{scene_.theme()->bg_color()};
			al_set_target_backbuffer(get<ALLEGRO_DISPLAY *>());
			al_reset_clipping_rectangle();
			al_clear_to_color(al_map_rgba(c.r, c.g, c.b, c.a));
		}
		return *this;
	}

	void display::update_position()
	{
		if (!hidden_) {
			int x, y;
			al_get_window_position(get<ALLEGRO_DISPLAY *>(), &x, &y);
			x_ = x / scale_factor_;
			y_ = y / scale_factor_;
		}
	}

	bool display::should_handle_event(const std::any &native_event)
	{
		if (hidden_) return false;

		auto *const target{event_target_display(native_event)};
		if (!target) return true;

		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event)};
		if (e.type == ALLEGRO_EVENT_TIMER && &timer::get(e.timer.source) == &redraw_timer_) return false;

		return target == get<ALLEGRO_DISPLAY *>();
	}

	void display::handle_event(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event)};

		if (!should_handle_event(e)) return;

		update_position();
		switch (e.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE: handle_display_closed(e); break;
			case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING: handle_drawing_paused(e); break;
			case ALLEGRO_EVENT_DISPLAY_RESIZE: handle_display_resized(e); break;
			case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING: handle_drawing_resumed(e); break;
			case ALLEGRO_EVENT_DISPLAY_SWITCH_IN: handle_display_switched_in(e); break;
			case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT: handle_display_switched_out(e); break;
			case ALLEGRO_EVENT_MOUSE_AXES: handle_mouse_axes_changed(e); break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: handle_mouse_button_pressed(e); break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP: handle_mouse_clicked(e); break;
			case ALLEGRO_EVENT_KEY_CHAR: handle_character_typed(e); break;
			case ALLEGRO_EVENT_KEY_DOWN: handle_key_pressed(e); break;
			case ALLEGRO_EVENT_KEY_UP: handle_key_released(e); break;
		}

		redraw_timer_.start();
	}

	void display::handle_mouse_axes_changed(const std::any &native_event)
	{
		if (!hidden_) {
			const auto e{mouse_event(native_event, scale_factor_)};
			auto &t{acquired_component_ ? *acquired_component_ : scene_.child_at_pos(e.x, e.y).value_or(scene_).get()};
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
		if (!hidden_) {
			const auto e{mouse_event(native_event, scale_factor_)};
			component &t = scene_.child_at_pos(e.x, e.y).value_or(scene_);
			acquired_component_ = last_event_target_ = &t;
			focused_component_ = t.focusable() ? &t : nullptr;
			t.trigger(events::mouse_button_pressed{e.button, e.x, e.y, e.z, e.w, t});
		}
	}

	void display::handle_mouse_clicked(const std::any &native_event)
	{
		if (!hidden_) {
			const auto e{mouse_event(native_event, scale_factor_)};
			auto &t{acquired_component_ ? *acquired_component_ : scene_.child_at_pos(e.x, e.y).value_or(scene_).get()};
			acquired_component_ = nullptr;
			last_event_target_ = &t;
			t.trigger(events::mouse_clicked{e.button, e.x, e.y, e.z, e.w, t});
		}
	}

	void display::handle_key_pressed(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).keyboard};
		if (!hidden_ && focused_component_) focused_component_->trigger(events::key_pressed{e.keycode, *focused_component_});
	}

	void display::handle_key_released(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).keyboard};
		if (!hidden_ && focused_component_) focused_component_->trigger(events::key_released{e.keycode, *focused_component_});
	}

	void display::handle_character_typed(const std::any &native_event)
	{
		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).keyboard};
		if (!hidden_ && focused_component_) {
			char chr[5];
			chr[al_utf8_encode(chr, e.unichar)] = '\0';
			focused_component_->trigger(events::character_typed{e.keycode, {chr, e.unichar}, *focused_component_});
		}
	}

	void display::handle_display_resized(const std::any &native_event)
	{
		if (hidden_) return;

		const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event).display};
		auto *const handle{clear().get<ALLEGRO_DISPLAY *>()};
		al_acknowledge_resize(handle);
		width_ = e.width / scale_factor_;
		height_ = e.height / scale_factor_;
		maximized_ = (ALLEGRO_MAXIMIZED == (al_get_display_flags(handle) & ALLEGRO_MAXIMIZED));
		on_resized.emit(*this);
		redraw();
	}

	void display::handle_display_switched_in(const std::any &)
	{
		minimized_ = false;
	}

	void display::handle_display_switched_out(const std::any &)
	{
		minimized_ = (ALLEGRO_MINIMIZED == (al_get_display_flags(get<ALLEGRO_DISPLAY *>()) & ALLEGRO_MINIMIZED));
	}

	void display::handle_drawing_paused(const std::any &)
	{
		if (!hidden_) al_acknowledge_drawing_halt(pause_drawing().get<ALLEGRO_DISPLAY *>());
	}

	void display::handle_drawing_resumed(const std::any &)
	{
		if (!hidden_) al_acknowledge_drawing_resume(resume_drawing().get<ALLEGRO_DISPLAY *>());
	}

	void display::handle_display_closed(const std::any &)
	{
		hide().on_closed.emit(*this);
	}
}

ALLEGRO_DISPLAY *create_display(const int width, const int height, const std::string_view title, const int flags)
{
	al_set_new_display_flags(ALLEGRO_OPENGL | flags);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	al_set_new_window_title(std::string{title}.c_str());
	auto display{al_create_display(width, height)};
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);
	return display;
}

ALLEGRO_MOUSE_EVENT mouse_event(const std::any &native_event, const float scale_factor)
{
	auto e{std::any_cast<const ALLEGRO_EVENT &>(native_event).mouse};
	e.x /= scale_factor;
	e.y /= scale_factor;
	e.dx /= scale_factor;
	e.dy /= scale_factor;
	return e;
}

ALLEGRO_DISPLAY *event_target_display(const std::any &native_event)
{
	const auto &e{std::any_cast<const ALLEGRO_EVENT &>(native_event)};
	switch (e.type) {
		case ALLEGRO_EVENT_JOYSTICK_AXIS:
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
		case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
			return nullptr;

		case ALLEGRO_EVENT_KEY_DOWN:
		case ALLEGRO_EVENT_KEY_UP:
		case ALLEGRO_EVENT_KEY_CHAR:
			return e.keyboard.display;

		case ALLEGRO_EVENT_MOUSE_AXES:
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		case ALLEGRO_EVENT_MOUSE_WARPED:
		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
		case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
			return e.mouse.display;

		case ALLEGRO_EVENT_TOUCH_BEGIN:
		case ALLEGRO_EVENT_TOUCH_END:
		case ALLEGRO_EVENT_TOUCH_MOVE:
		case ALLEGRO_EVENT_TOUCH_CANCEL:
			return e.touch.display;

		case ALLEGRO_EVENT_TIMER:
			return nullptr;

		case ALLEGRO_EVENT_DISPLAY_EXPOSE:
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		case ALLEGRO_EVENT_DISPLAY_LOST:
		case ALLEGRO_EVENT_DISPLAY_FOUND:
		case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
		case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
		case ALLEGRO_EVENT_DISPLAY_ORIENTATION:
		case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING:
		case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING:
		case ALLEGRO_EVENT_DISPLAY_CONNECTED:
		case ALLEGRO_EVENT_DISPLAY_DISCONNECTED:
			return e.display.source;

		default:
			return nullptr;
	}
}

float default_scale_factor()
{ return dpi() / 96.0f; }

#ifdef _WIN32
#include <allegro5/allegro_windows.h>
int dpi()
{
	const auto dc{GetDC(nullptr)};
	const auto dpi{GetDeviceCaps(dc, LOGPIXELSX)};
	ReleaseDC(nullptr, dc);
	return dpi;
}

ag::display &ag::display::set_minimized(const bool minimized)
{
	if (!hidden_) {
		ShowWindow(al_get_win_window_handle(get<ALLEGRO_DISPLAY *>()), minimized ? SW_MINIMIZE : SW_RESTORE);
	}
	minimized_ = minimized;
	return *this;
}

#else

int dpi()
{ return 96; }

ag::display &ag::display::set_minimized(const bool)
{ return *this; }
#endif
