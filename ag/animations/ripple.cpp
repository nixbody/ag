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
			if (running_ && (radius_ += 0.1f + 0.0125f * component_.width()) > component_.width()) {
				timer_.stop();
				radius_ = 0.0f;
				running_ = false;
			}
		});
	}

	ripple &ripple::operator()(float x, float y)
	{
		component_.overlay_x = [this, x] { return x - radius_; };
		component_.overlay_y = [this, y] { return y - radius_; };
		radius_ = 0.0f;
		running_ = true;
		timer_.start();
		return *this;
	}
}
