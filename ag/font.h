#pragma once

#include "color.h"

#include <any>
#include <string>

namespace ag
{
	/* Font. */
	class font final
	{
	public:
		/* Text alignment. */
		enum class alignment {left, right, center};

		/* Create a new font with the given size from the given resource. */
		font(const std::string &resource, const int size);

		/* Destructor. */
		~font() = default;

		/* Get usual line height specified by this font. */
		float line_height() const;

		/* Get width of the given text when using this font. */
		float text_width(const std::string &text) const;

		/* Draw the given text using this font. */
		void draw_text(
			const std::string &text,
			const float x, 
			const float y,
			const float max_width,
			const color &color = color{0, 0, 0},
			const float line_height = 0.0f,
			const alignment align = alignment::left
		) const;

	private:
		/* Handle to a native underlaying (implmentation specific) font resource. */
		std::any native_handle_;
	};
}
