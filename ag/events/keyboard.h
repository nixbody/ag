#pragma once

#include "../key.h"

#include <cstdint>
#include <string>

namespace ag { class component; }
namespace ag::events
{
	/* Triggered when the target component is focused and a key is pressed. */
	struct key_pressed final
	{
		/* The key that was pressed. */
		const key key;

		/* Target component. */
		component &target;
	};

	/* Triggered when the target component is focused and a key is released. */
	struct key_released final
	{
		/* The key that was released. */
		const key key;

		/* Target component. */
		component &target;
	};

	/* Triggered when the target component is focused and a character is typed. */
	struct character_typed final
	{
		/* String representing a UTF-8 character. */
		class utf8_char final : public std::string
		{
		public:
			/* Create a new UTF-8 character. */
			utf8_char(const char str[], std::int32_t code_point): std::string{str}, code_point_{code_point}
			{}

			/* Tell whether or not this character is printable. */
			constexpr bool is_printable() const noexcept
			{ return code_point_ > 0x1f && code_point_ != 0x7f && (code_point_ < 0x80 || code_point_ > 0x9f); }

		private:
			/* This character's code point. */
			const std::int32_t code_point_;
		};

		/* The key that was pressed. */
		const key key;

		/* The UTF-8 character that was typed. */
		const utf8_char character;

		/* Target component. */
		component &target;
	};
}
