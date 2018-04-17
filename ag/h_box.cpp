#include "h_box.h"

namespace ag
{
	float h_box::child_x(const component &child) const
	{
		const auto &s = style();
		float content_width{0.0f}, x = s.x();

		for (const auto &crw : children()) {
			const auto &c = crw.get();
			const auto &cs = c.style();
			const auto cm = cs.margin();

			if (&c == &child) x += content_width + cm.left;
			if (!c.hidden()) content_width += cs.width() + cm.left + cm.right;
		}

		switch (s.align()) {
			case style_type::alignment::center:
			case style_type::alignment::top_center:
			case style_type::alignment::bottom_center:
				return x + 0.5f * (s.width() - content_width);

			case style_type::alignment::top_right:
			case style_type::alignment::center_right:
			case style_type::alignment::bottom_right:
				return x + s.width() - content_width - s.border().thickness - s.padding().right;

			default: return x + s.border().thickness + s.padding().left;
		}
	}
}
