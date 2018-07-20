#pragma once

#include "border.h"
#include "color.h"
#include "component_theme.h"
#include "display.h"
#include "events/keyboard.h"
#include "events/mouse.h"
#include "font.h"
#include "insets.h"
#include "prop.h"
#include "signal.h"

#include <functional>
#include <memory>
#include <string_view>
#include <utility>

namespace ag
{
	class box;
	class component;

	using component_ref = std::reference_wrapper<component>;

	/* Base class for UI components. */
	class component
	{
		friend box;

	public:
		/* Theme used by this component. */
		prop<std::shared_ptr<component_theme>> theme;

		/* Tells whether or not this component is supposed to be visible and/or is focusable. */
		prop<bool> visible{true}, focusable{true};

		/* Position coordinates, dimensions and corners' radius. */
		prop<float> x, y, width, height, line_height, radius{0.0f};

		/* Background and text color. */
		prop<color> bg_color{0, 0, 0, 0}, text_color;

		/* Margin and padding. */
		prop<insets> margin{0.0f}, padding{0.0f};

		/* Border. */
		prop<border> border{0.0f, color{0, 0, 0, 0}};

		/* Text font. */
		prop<font> font;

		/* Text alignment. */
		prop<font::alignment> text_align;

		/* Text label. */
		prop<std::string_view> text{""};

		/* Overlay position, size and radius. */
		prop<float>
			overlay_x{[this] { return x(); }},
			overlay_y{[this] { return y(); }},
			overlay_width{[this] { return width(); }},
			overlay_height{[this] { return height(); }},
			overlay_radius{[this] { return radius(); }};

		/* Overlay color. */
		prop<color>
			overlay_color{0, 0, 0, 0};

		/* Signal which is emitted when one or more mouse axes changed over this component. */
		signal<const events::mouse_axes_changed &> on_mouse_axes_changed;

		/* Signal which is emitted when mouse cursor entered this component. */
		signal<const events::mouse_entered &> on_mouse_entered;

		/* Signal which is emitted when mouse cursor left this component. */
		signal<const events::mouse_left &> on_mouse_left;

		/* Signal which is emitted when a mouse button was pressed over this component. */
		signal<const events::mouse_button_pressed &> on_mouse_button_pressed;

		/* Signal which is emitted when this component was clicked. */
		signal<const events::mouse_clicked &> on_clicked;

		/* Signal which is emitted when this component is focused and a key was pressed. */
		signal<const events::key_pressed &> on_key_pressed;

		/* Signal which is emitted when this component is focused and a key was released. */
		signal<const events::key_released &> on_key_released;

		/* Signal which is emitted when this component is focused and a character was typed. */
		signal<const events::character_typed &> on_character_typed;

		/* Default constructor. */
		component() = default;

		/* Prevents copying. */
		component(const component &) = delete;

		/* Prevents moving. */
		component(component &&) = delete;

		/* Virtual destructor. */
		virtual ~component() noexcept = default;

		/* Prevents copy-assignment. */
		component &operator=(const component &) = delete;

		/* Prevents move-assignment. */
		component &operator=(component &&) = delete;

		/* Draw this component on the screen. */
		void draw() const;

		/* Tell whether or not this component is attached to a display. */
		bool has_display() const noexcept
		{ return display_; }

		/* Get the display on which this component is drawn. */
		display &display() noexcept
		{ return *display_; }

		/* Tell whether or not this component has a parent. */
		bool has_parent() const noexcept
		{ return parent_; }

		/* Get parent of this component. */
		box &parent() noexcept
		{ return *parent_; }

		/* Trigger the given event on this component. */
		component &trigger(const events::mouse_axes_changed &event)
		{ return trigger(on_mouse_axes_changed, event); }

		/* Trigger the given event on this component. */
		component &trigger(const events::mouse_entered &event)
		{ return trigger(on_mouse_entered, event); }

		/* Trigger the given event on this component. */
		component &trigger(const events::mouse_left &event)
		{ return trigger(on_mouse_left, event); }

		/* Trigger the given event on this component. */
		component &trigger(const events::mouse_button_pressed &event)
		{ return trigger(on_mouse_button_pressed, event); }

		/* Trigger the given event on this component. */
		component &trigger(const events::mouse_clicked &event)
		{ return trigger(on_clicked, event); }

		/* Trigger the given event on this component. */
		component &trigger(const events::key_pressed &event)
		{ return trigger(on_key_pressed, event); }

		/* Trigger the given event on this component. */
		component &trigger(const events::key_released &event)
		{ return trigger(on_key_released, event); }

		/* Trigger the given event on this component. */
		component &trigger(const events::character_typed &event)
		{ return trigger(on_character_typed, event); }

	protected:
		/* Call the given target and apply current scale factor on all the arguments. */
		template <typename U = float, typename Invocable, typename ... T>
		auto scaled(Invocable &&target, T && ... args) const
		{ return target(U(std::forward<T>(args) * (display_ ? display_->scale_factor() : 1.0f))...); }

		/* Draw the given text onto this component. */
		inline void draw_text(std::string_view text) const;

	private:
		/* Display on which this component is drawn. */
		ag::display *display_{nullptr};

		/* Parent of this component. */
		box *parent_{nullptr};

		/* Attach this component to the given display. */
		virtual void set_display(ag::display &display)
		{ display_ = &display; }

		/* Draw this component's border. */
		virtual void draw_border(float x, float y, float width, float height, float radius, const ag::border &border) const;

		/* Draw this component's background. */
		virtual void draw_background(float x, float y, float width, float height, float radius, const ag::border &border) const;

		/* Draw a layer over this component. */
		virtual void draw_overlay() const;

		/* Draw this component's content. */
		virtual void draw_content() const
		{ draw_text(text()); }

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_axes_changed &)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_entered &)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_left &)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_button_pressed &)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_clicked &)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::key_pressed &)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::key_released &)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::character_typed &)
		{}

		/* Trigger the given event on this component and then emit the given signal. */
		template <typename Signal, typename Event>
		component &trigger(Signal &&signal, Event &&event)
		{
			event_triggered(std::forward<Event>(event));
			signal.emit(std::forward<Event>(event));
			return *this;
		}
	};

	void component::draw_text(const std::string_view text) const
	{
		if (text.empty()) return;

		const auto p{padding()};
		const auto b{border()};
		auto x{this->x() + p.left + b.thickness}, w{width() - p.left - p.right - 2.0f * b.thickness};

		const auto a{text_align()};
		switch (a) {
			case font::alignment::center: x += 0.5f * w; break;
			case font::alignment::right: x += w; break;
			case font::alignment::left: break;
		}

		font().draw_text(text, x, y() + p.top + b.thickness, w, text_color(), line_height(), a);
	}
}
