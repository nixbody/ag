#pragma once

#include "../timer.h"

namespace ag { class component; }
namespace ag::animations
{
	/* Ripple effect. */
	class ripple final
	{
	public:
		/* Animate the given component. */
		ripple(component &component);

		/* Re/start this animation on the given coordinates. */
		ripple &operator()(float x, float y);

	private:
		/* Animation timer. */
		timer timer_{10.0ms, true};

		/* Component being animated. */
		component &component_;

		/* Current radius. */
		float radius_{0.0f};
	};
}
