#include "v_box.h"

namespace ag
{
	float v_box::child_y(const component &child) const
	{
		const auto &s = style();
		float content_height{0.0f}, y = s.y();

		for (const auto &crw : children()) {
			const auto &c = crw.get();
			const auto &cs = c.style();
			const auto cm = cs.margin();

			if (&c == &child) y += content_height + cm.top;
			if (!c.hidden()) content_height += cs.height() + cm.top + cm.bottom;
		}

		switch (s.align()) {
			case style_type::alignment::center:
			case style_type::alignment::center_left:
			case style_type::alignment::center_right:
				return y + 0.5f * (s.height() - content_height);

			case style_type::alignment::bottom_left:
			case style_type::alignment::bottom_right:
			case style_type::alignment::bottom_center:
				return y + s.height() - content_height - s.border().thickness - s.padding().bottom;

			default: return y + s.border().thickness + s.padding().top;
		}
	}
}
