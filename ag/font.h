#pragma once

#include "color.h"

#include <any>
#include <array>
#include <cstddef>
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
		constexpr font(std::array<std::byte, ArraySize> &resource, float size) noexcept:
			font{resource.data(), ArraySize, size}
		{}

		/* Create a new font with the given size from the given resource. */
		constexpr font(std::byte *resource, std::size_t resource_size, float size) noexcept:
			resource_{resource}, resource_size_{resource_size}, size_{size}
		{}

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
		/* Font resource. */
		std::byte *const resource_;

		/* Font resource size. */
		const std::size_t resource_size_;

		/* Size of this font. */
		const float size_;

		/* Handle to a native underlaying (implmentation specific) font resource. */
		mutable std::any native_handle_;

		/* Load this font with the given size. */
		std::any load(float size) const;

		/* Get handle to this font's native resource. */
		template <typename T>
		T get() const
		{ return std::any_cast<T>(!native_handle_.has_value() ? native_handle_ = load(size_) : native_handle_); }
	};
}
