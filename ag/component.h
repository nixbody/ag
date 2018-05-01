#pragma once

#include "border.h"
#include "color.h"
#include "events/mouse.h"
#include "font.h"
#include "insets.h"
#include "prop.h"
#include "signal.h"

#include <functional>
#include <string_view>

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
		/* Tells whether or not this component is supposed to be visible. */
		prop<bool> visible{true};

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
		prop<std::string_view> text;

		/* Signal which is emitted when one or more mouse axes changed over this component. */
		signal<const events::mouse_axes_changed &> on_mouse_axes_changed;

		/* Signal which is emitted when mouse cursor entered this component. */
		signal<const events::mouse_entered &> on_mouse_entered;

		/* Signal which is emitted when mouse cursor left this component. */
		signal<const events::mouse_left &> on_mouse_left;

		/* Signal which is emitted when a mouse button was pressed over this component. */
		signal<const events::mouse_button_pressed &> on_mouse_button_pressed;

		/* Signal which is emitted when a mouse button was released over this component. */
		signal<const events::mouse_button_released &> on_mouse_button_released;

		/* Signal which is emitted when this component was clicked. */
		signal<const events::mouse_clicked &> on_clicked;

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
		inline void draw() const;

		/* Tell whether or not this component has a parent. */
		constexpr bool has_parent() const noexcept
		{ return parent_; }

		/* Get parent of this component. */
		constexpr const box &parent() const noexcept
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
		component &trigger(const events::mouse_button_released &event)
		{ return trigger(on_mouse_button_released, event); }

		/* Trigger the given event on this component. */
		component &trigger(const events::mouse_clicked &event)
		{ return trigger(on_clicked, event); }

	private:
		/* Parent of this component. */
		const box *parent_{nullptr};

		/* Draw this component's border. */
		virtual void draw_border() const;

		/* Draw this component's background. */
		virtual void draw_background() const;

		/* Draw this component's content. */
		virtual void draw_content() const;

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_axes_changed &event)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_entered &event)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_left &event)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_button_pressed &event)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_button_released &event)
		{}

		/* Will be called when the given event was triggered on this component. */
		virtual void event_triggered(const events::mouse_clicked &event)
		{}

		/* Trigger the given event on this component and then emit the given signal. */
		template <typename Signal, typename Event>
		component &trigger(const Signal &signal, const Event &event);
	};

	void component::draw() const
	{
		if (!visible()) return;

		draw_border();
		draw_background();
		draw_content();
	}

	template <typename Signal, typename Event>
	component &component::trigger(const Signal &signal, const Event &event)
	{
		event_triggered(event);
		signal.emit(event);
		return *this;
	}
}
