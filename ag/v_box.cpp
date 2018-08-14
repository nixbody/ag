#include "v_box.h"

namespace ag
{
	float v_box::first_child_y() const
	{
		auto content_height{0.0f};

		for (const component &c : children()) {
			if (c.visible()) {
				const auto cm{c.margin()};
				content_height += c.height() + cm.top + cm.bottom;
			}
		}

		const auto y{this->y() + children().front().get().margin().top};
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

	float v_box::child_y(const component &child) const
	{
		if (const auto i{child_index(child)}; i > 0) {
			const component &prev = children()[i - 1], &c = children()[i];
			return prev.y() + prev.height() + prev.margin().bottom + c.margin().top;
		} else {
			return first_child_y();
		}
	}
}
