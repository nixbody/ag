#pragma once

namespace ag { class component; }
namespace ag::events
{
	/* Triggered when one or more mouse axis changed. */
	struct mouse_axes_changed final
	{
		/* Mouse coordinates deltas. */
		struct { const int x, y, z, w; } const deltas;

		/* Mouse coordinates. */
		const int x, y, z, w;

		/* Target component. */
		component &target;
	};

	/* Triggered when mouse is dragged. */
	struct mouse_dragged final
	{
		/* Mouse coordinates deltas. */
		struct { const int x, y, z, w; } const deltas;

		/* Mouse coordinates. */
		const int x, y, z, w;

		/* Target component. */
		component &target;
	};

	/* Triggered when mouse cursor entered the target component. */
	struct mouse_entered final
	{
		/* Mouse coordinates deltas. */
		struct { const int x, y, z, w; } const deltas;

		/* Mouse coordinates. */
		const int x, y, z, w;

		/* Target component. */
		component &target;
	};

	/* Triggered when mouse cursor left the target component. */
	struct mouse_left final
	{
		/* Mouse coordinates deltas. */
		struct { const int x, y, z, w; } const deltas;

		/* Mouse coordinates. */
		const int x, y, z, w;

		/* Target component. */
		component &target;
	};

	/* Triggered when a mouse button was pressed. */
	struct mouse_button_pressed final
	{
		/* Mouse button which was pressed. */
		const unsigned button;

		/* Mouse coordinates. */
		const int x, y, z, w;

		/* Target component. */
		component &target;

		/* Pressed button identifier. */
		const bool button_primary{button == 1}, button_secondary{button == 2};
	};

	/* Triggered when the target component is clicked. */
	struct mouse_clicked final
	{
		/* Mouse button which was clicked. */
		const unsigned button;

		/* Mouse coordinates. */
		const int x, y, z, w;

		/* Target component. */
		component &target;

		/* Pressed button identifier. */
		const bool button_primary{button == 1}, button_secondary{button == 2};
	};
}
