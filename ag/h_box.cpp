#include "h_box.h"

namespace ag
{
	float h_box::child_x(const component &child) const
	{
		auto content_width{0.0f}, x{this->x()};

		for (const component &c : children()) {
			const auto cm{c.margin()};

			if (&c == &child) x += content_width + cm.left;
			if (c.visible()) content_width += c.width() + cm.left + cm.right;
		}

		switch (align()) {
			case box::alignment::center:
			case box::alignment::top_center:
			case box::alignment::bottom_center:
				return x + 0.5f * (width() - content_width);

			case box::alignment::top_right:
			case box::alignment::center_right:
			case box::alignment::bottom_right:
				return x + width() - content_width - border().thickness - padding().right;

			default: return x + border().thickness + padding().left;
		}
	}
}
