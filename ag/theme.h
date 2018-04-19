#pragma once

#include "color.h"
#include "font.h"
#include "insets.h"

#include <cstdlib>
#include <utility>

namespace ag
{
	/* Base for application themes. */
	struct theme
	{
		template <typename T>
		friend void set_theme(T &&theme);
		friend const theme &get_theme();

		/* Destructor. */
		virtual ~theme() = default;

		/* Text font. */
		virtual font text_font() const = 0;

		/* Text color. */
		virtual color text_color() const = 0;

		/* Line height. */
		virtual float line_height() const = 0;

		/* Button radius. */
		virtual float button_radius() const = 0;

		/* Button padding. */
		virtual insets button_padding() const = 0;

		/* Button font. */
		virtual font button_font() const = 0;

		/* Button primary color. */
		virtual color button_primary_color() const = 0;

		/* Button secondary color. */
		virtual color button_secondary_color() const = 0;

	private:
		/* Currently set theme. */
		static const theme *current_;
	};

	/* Set the given theme. */
	template <typename T>
	void set_theme(T &&theme)
	{
		if (!theme::current_) {
			delete theme::current_;
		} else {
			std::atexit([] { delete theme::current_; });
		}

		theme::current_ = new T{std::forward<T>(theme)};
	}

	/* Get currently set theme. */
	const theme &get_theme();
}
