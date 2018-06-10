#pragma once

#include "../color.h"
#include "../timer.h"

#include <optional>

namespace ag::animations
{
	/* Ripple effect. */
	class ripple final
	{
	public:
		/* Initialize animation. */
		ripple()
		{
			timer_.on_ticked([this](const auto &) {
				if ((current_radius_ += 5.0f) > radius_) {
					current_radius_ = 0.0f;
					timer_.pause();
				}
			});
		}

		/* Re/start this animation. */
		ripple &operator()(float x, float y, float radius, const color &color)
		{
			x_ = x; y_ = y; radius_ = radius; current_radius_ = 0.0f;
			color_.emplace(color.r, color.g, color.b, color.a);
			timer_.resume();
			return *this;
		}

		/* Draw current frame. */
		void draw_frame() const;

	private:
		/* Animation timer. */
		timer timer_{10.0ms, true};

		/* Coordinates, radius and current radius. */
		float x_, y_, radius_, current_radius_;

		/* Ripple color. */
		std::optional<color> color_{color{0, 0, 0, 0}};
	};
}
