#include "ripple.h"

#include "../component.h"

namespace ag::animations
{
	ripple::ripple(component &component): component_{component}
	{
		component_.overlay_width = [this] { return 2.0f * radius_; };
		component_.overlay_height = [this] { return 2.0f * radius_; };
		component_.overlay_radius = [this] { return radius_; };
		component_.overlay_color = {40, 40, 40, 30};

		timer_.on_ticked([this](const auto &) {
			if ((radius_ += 4.0f) > component_.width()) {
				radius_ = 0.0f;
				timer_.pause();
			}
		});
	}

	ripple &ripple::operator()(float x, float y)
	{
		component_.overlay_x = [this, x] { return x - radius_; };
		component_.overlay_y = [this, y] { return y - radius_; };
		radius_ = 0.0f;
		timer_.resume();
		return *this;
	}
}
