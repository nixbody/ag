#pragma once

namespace ag
{
	/* Insets. */
	struct insets final
	{
		/* Individual insets. */
		const float top, right, bottom, left;

		/* Set all insets at once. */
		insets(const float all);

		/* Create new insets. */
		insets(const float top_bottom, const float right_left);

		/* Create new insets. */
		insets(const float top, const float right, const float bottom, const float left);
	};
}
