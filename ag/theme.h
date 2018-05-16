#pragma once

#include "color.h"
#include "font.h"
#include "insets.h"

#include <cstdlib>
#include <utility>

namespace ag
{
	/* Base for application themes. */
	class theme
	{
		template <typename T>
		friend void set_theme(T &&theme);
		friend constexpr const theme &get_theme() noexcept;

	public:
		/* Destructor. */
		virtual ~theme() noexcept = default;

		/* Background color. */
		virtual color bg_color() const noexcept = 0;

		/* Text font. */
		virtual font text_font() const = 0;

		/* Text color. */
		virtual color text_color() const noexcept = 0;

		/* Line height. */
		virtual float line_height() const noexcept = 0;

		/* Button radius. */
		virtual float button_radius() const noexcept = 0;

		/* Button padding. */
		virtual insets button_padding() const noexcept = 0;

		/* Button font. */
		virtual font button_font() const = 0;

		/* Button primary color. */
		virtual color button_primary_color() const noexcept = 0;

		/* Button secondary color. */
		virtual color button_secondary_color() const noexcept = 0;

	private:
		/* Currently set theme. */
		static inline const theme *current_{nullptr};
	};

	/* Set the given theme. */
	template <typename T>
	void set_theme(T &&theme)
	{
		if (theme::current_) {
			delete theme::current_;
		} else {
			std::atexit([] { delete theme::current_; });
		}

		theme::current_ = new T{std::forward<T>(theme)};
	}

	/* Get currently set theme. */
	constexpr const theme &get_theme() noexcept
	{ return *theme::current_; }
}
