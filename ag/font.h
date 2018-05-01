#pragma once

#include "color.h"

#include <any>
#include <array>
#include <string_view>

namespace ag
{
	/* Font. */
	class font final
	{
	public:
		/* Text alignment. */
		enum class alignment {left, right, center};

		/* Create a new font with the given size from the given resource. */
		template <auto ArraySize>
		constexpr font(std::array<std::byte, ArraySize> &resource, int size): font{resource.data(), resource.size(), size}
		{}

		/* Create a new font with the given size from the given resource. */
		font(void *resource, std::size_t resource_size, int size);

		/* Get usual line height specified by this font. */
		float line_height() const;

		/* Get width of the given text when using this font. */
		float text_width(std::string_view text) const;

		/* Draw the given text using this font. */
		void draw_text(
			std::string_view text,
			float x,
			float y,
			float max_width,
			const color &color = {0, 0, 0},
			float line_height = 0.0f,
			alignment align = alignment::left
		) const;

	private:
		/* Handle to a native underlaying (implmentation specific) font resource. */
		std::any native_handle_;
	};
}
