#pragma once

namespace ag { class slider; }
namespace ag::events
{
	/* Trigerred when a slider thumb position changes. */
	struct pos_changed final
	{
		/* New position of the slider thumb. */
		const double pos;

		/* Target slider. */
		slider &target;
	};
}
