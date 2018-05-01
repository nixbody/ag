#pragma once

namespace ag
{
	/* Insets. */
	struct insets final
	{
		/* Individual insets. */
		const float top, right, bottom, left;

		/* Set all the insets at once. */
		constexpr insets(float all) noexcept: top{all}, right{all}, bottom{all}, left{all}
		{}

		/* Create new insets. */
		constexpr insets(float top_bottom, float right_left) noexcept:
			top{top_bottom}, right{right_left}, bottom{top_bottom}, left{right_left}
		{}

		/* Create new insets. */
		constexpr insets(float top, float right, float bottom, float left) noexcept:
			top{top}, right{right}, bottom{bottom}, left{left}
		{}
	};
}
