#pragma once

#include "box.h"
#include "event_queue.h"
#include "signal.h"
#include "timer.h"

#include <any>
#include <string_view>

namespace ag
{
	/* Represents a graphical window or fullscreen frame. */
	class display final
	{
	public:
		/* Signal which is emitted when this display is closed. */
		signal<display &> on_closed;

		/* Signal which is emitted when this display is resized. */
		signal<display &> on_resized;

		/* Create a new display with the given size. */
		display(int width, int height, std::string_view title = {}, event_queue &event_queue = default_event_queue());

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

		/* Get the width of this display. */
		int width() const;

		/* Get the height of this display. */
		int height() const;

		/* Set the minimum size of this display. */
		display &set_min_size(int width, int height);

		/* Draw the given box every time this display is redrawn. */
		display &draw(box &scene);

		/* Redraw this display. */
		display &redraw(bool force = false);

		/* Pause drawing of this display. */
		constexpr display &pause_drawing()
		{ drawing_paused_ = true; return *this; }

		/* Resume drawing of this display. */
		constexpr display &resume_drawing()
		{ drawing_paused_ = false; return *this; }

	private:
		/* Handle to the native underlaying (implementation specific) display. */
		const std::any native_handle_;

		/* Event queue associated with this display. */
		event_queue &event_queue_;

		/* Connection between this display's slot and the associated event queue's signal. */
		const decltype(event_queue_.on_event_occured)::connection on_event_occured;

		/* Timer responsible for periodic (if necessary) redrawing of this display. */
		timer redraw_timer_{40.0ms};

		/* Tells whether or not this display should be redrawn and whether or not drawing is paused. */
		bool should_redraw_{true}, drawing_paused_{false};

		/* Box which is drawn every time this display is redrawn. */
		box *scene_{nullptr};

		/* Acquired component gets all the events and focused component gets all the keyboard events. */
		component *acquired_component_{nullptr}, *last_event_target_{nullptr}, *focused_component_{nullptr};

		/* Clear this display. */
		display &clear();

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
	};
}
