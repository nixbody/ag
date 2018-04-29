#pragma once

namespace ag
{
	/* Insets. */
	struct insets final
	{
		/* Individual insets. */
		const float top, right, bottom, left;

		/* Set all insets at once. */
		insets(float all);

		/* Create new insets. */
		insets(float top_bottom, float right_left);

		/* Create new insets. */
		insets(float top, float right, float bottom, float left);
	};
}
