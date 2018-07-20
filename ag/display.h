#pragma once

#include "event_queue.h"
#include "signal.h"
#include "timer.h"

#include <any>
#include <string_view>

namespace ag
{
	class component;
	class box;

	/* Represents a graphical window or fullscreen frame. */
	class display final
	{
	public:
		/* Signals which are emitted by this display. */
		signal<display &> on_closed, on_resized;

		/* Create a new display with the given size and title. */
		display(float width, float height, std::string_view title = {}, event_queue &event_queue = default_event_queue());

		/* Disable copying. */
		display(const display &) = delete;

		/* Disable moving. */
		display(display &&) = delete;

		/* Tear down this display. */
		~display() noexcept;

		/* Disable copy-assignment. */
		display &operator=(const display &) = delete;

		/* Disable move-assignment. */
		display &operator=(display &&) = delete;

		/* Get the current X coordinate of this display. */
		float x() const noexcept
		{ return x_; }

		/* Get the current Y coordinate of this display. */
		float y() const noexcept
		{ return y_; }

		/* Get the width of this display. */
		float width() const noexcept
		{ return width_; }

		/* Get the height of this display. */
		float height() const noexcept
		{ return height_; }

		/* Get the scale factor of this display. */
		float scale_factor() const noexcept
		{ return scale_factor_; }

		/* Get the scene associated with this display. */
		constexpr box &scene() noexcept
		{ return scene_; }

		/* Tell whether or not this display has a frame. */
		bool frameless() const noexcept
		{ return frameless_; }

		/* Tell whether or not this display is taking entire screen. */
		bool fullscreen() const noexcept
		{ return fullscreen_; }

		/* Tell whether or not this display is maximized. */
		bool maximized() const noexcept
		{ return maximized_; }

		/* Tell whether or not this display is minimized. */
		bool minimized() const noexcept
		{ return minimized_; }

		/* Tell whether or not this display is hidden. */
		bool hidden() const noexcept
		{ return hidden_; }

		/* Set the minimum size of this display. */
		display &set_min_size(float width, float height);

		/* Resize this display. */
		display &resize(float width, float height);

		/* Scale this display. */
		display &scale(float factor, bool resize_display = true);

		/* Move this display to the center of the screen. */
		display &center();

		/* Move this display to the center of the given display. */
		display &center(display &parent);

		/* Move this display to the given position. */
		display &move(float x, float y);

		/* Set whether or not this display has a frame. */
		display &set_frameless(bool frameless = true);

		/* Set whether or not this display should take entire screen. */
		display &set_fullscreen(bool fullscreen = true);

		/* Set whether or not this display is maximized. */
		display &set_maximized(bool maximized = true);

		/* Set whether or not this display is minimized. */
		display &set_minimized(bool minimized = true);

		/* Hide this display. */
		display &hide();

		/* Show this display. */
		display &show();

		/* Show this display in the center of the screen. */
		display &show_centered()
		{ return center().show(); }

		/* Show this display in the center of the given display. */
		display &show_centered(display &parent)
		{ return center(parent).show(); }

		/* Limit framerate of this display. */
		display &limit_fps(unsigned limit)
		{ redraw_timer_.set_tick_interval(timer::seconds{1.0 / limit}); return *this; }

		/* Pause drawing of this display. */
		constexpr display &pause_drawing() noexcept
		{ drawing_paused_ = true; return *this; }

		/* Resume drawing of this display. */
		constexpr display &resume_drawing() noexcept
		{ drawing_paused_ = false; return *this; }

		/* Redraw this display. */
		display &redraw();

	private:
		/* Handle to the native underlaying (implementation specific) display. */
		std::any native_handle_;

		/* Event queue associated with this display. */
		event_queue &event_queue_;

		/* Connection between this display's slot and the associated event queue's signal. */
		const decltype(event_queue_.on_event_occured)::connection on_event_occured;

		/* Ticking till another frame is drawn. */
		timer redraw_timer_{33ms, false};

		/* Position, dimensions and scale factor of this display. */
		float x_{0.0f}, y_{0.0f}, width_{0.0}, height_{0.0}, scale_factor_{0.0};

		/* Various properties of this display. */
		bool resizable_{true}, frameless_{false}, fullscreen_{false}, maximized_{false}, minimized_{false}, hidden_{false};

		/* Tells whether or not drawing of this display is paused. */
		bool drawing_paused_{false};

		/* This display's title. */
		std::string_view title_;

		/* Scene associated with this display. */
		box &scene_;

		/* Acquired component gets all the events and focused component gets all the keyboard events. */
		component *acquired_component_{nullptr}, *last_event_target_{nullptr}, *focused_component_;

		/* Clear this display. */
		display &clear();

		/* Update information about position of this display. */
		void update_position();

		/* Tell whether or not this display should handle the given event. */
		bool should_handle_event(const std::any &native_event);

		/* Handle the given event. */
		void handle_event(const std::any &native_event);

		/* Handle the given mouse event. */
		void handle_mouse_axes_changed(const std::any &native_event);

		/* Handle the given mouse event. */
		void handle_mouse_button_pressed(const std::any &native_event);

		/* Handle the given mouse event. */
		void handle_mouse_clicked(const std::any &native_event);

		/* Handle the given keyboard event. */
		void handle_key_pressed(const std::any &native_event);

		/* Handle the given keyboard event. */
		void handle_key_released(const std::any &native_event);

		/* Handle the given keyboard event. */
		void handle_character_typed(const std::any &native_event);

		/* Handle the given display event. */
		void handle_display_resized(const std::any &native_event);

		/* Handle the given display event. */
		void handle_display_switched_in(const std::any &native_event);

		/* Handle the given display event. */
		void handle_display_switched_out(const std::any &native_event);

		/* Handle the given display event. */
		void handle_drawing_paused(const std::any &native_event);

		/* Handle the given display event. */
		void handle_drawing_resumed(const std::any &native_event);

		/* Handle the given display event. */
		void handle_display_closed(const std::any &native_event);

		/* Get handle to the native underlaying display and cast it to the given type. */
		template <typename T>
		T get();
	};
}
