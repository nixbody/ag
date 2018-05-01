#include "v_box.h"

namespace ag
{
	float v_box::child_y(const component &child) const
	{
		auto content_height{0.0f}, y{this->y()};

		for (const component &c : children()) {
			const auto cm{child.margin()};

			if (&c == &child) y += content_height + cm.top;
			if (child.visible()) content_height += child.height() + cm.top + cm.bottom;
		}

		switch (align()) {
			case box::alignment::center:
			case box::alignment::center_left:
			case box::alignment::center_right:
				return y + 0.5f * (height() - content_height);

			case box::alignment::bottom_left:
			case box::alignment::bottom_right:
			case box::alignment::bottom_center:
				return y + height() - content_height - border().thickness - padding().bottom;

			default: return y + border().thickness + padding().top;
		}
	}
}
