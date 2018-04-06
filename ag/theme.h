#pragma once

#include "font.h"

#include <optional>
#include <utility>

namespace ag
{
	/* Base for application themes. */
	struct theme
	{
		template <typename T>
		friend void set_theme(T &&theme)
		{
			theme::current_ = std::forward<T>(theme);
		}

		friend const theme &get_theme()
		{
			return *theme::current_;
		}

		/* Text font. */
		const font font;

	private:
		/* Currently set theme. */
		static std::optional<theme> current_;
	};

	/* Set the given theme. */
	template <typename T>
	void set_theme(T &&theme);

	/* Get currently set theme. */
	const theme &get_theme();
}
