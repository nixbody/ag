#include "h_box.h"

namespace ag
{
	float h_box::first_child_x() const
	{
		auto content_width{0.0f};
		for (const component &c : children()) {
			if (c.visible()) {
				const auto cm{c.margin()};
				content_width += c.width() + cm.left + cm.right;
			}
		}

		const auto x{this->x() + children().front().get().margin().left};
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

	float h_box::child_x(const component &child) const
	{
		if (const auto i{child_index(child)}; i > 0) {
			const component &prev = children()[i - 1], &c = children()[i];
			return prev.x() + prev.width() + prev.margin().right + c.margin().left;
		} else {
			return first_child_x();
		}
	}
}
