#pragma once

#include "font.h"

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
