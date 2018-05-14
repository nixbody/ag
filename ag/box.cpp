#include "box.h"

#include <algorithm>

namespace ag
{
	std::optional<component_ref> box::child_at_pos(const float x, const float y) const
	{
		component *child{nullptr};
		for (component &c : children_refs_) {
			const auto cx{c.x()}, cy{c.y()}, cw{c.width()}, ch{c.height()};

			if (
				const auto *const cb{dynamic_cast<const box *>(&c)};
				cb && (child = &cb->child_at_pos(x, y).value_or(*child).get())
			) continue;

			if (c.visible() && x >= cx && x < cx + cw && y >= cy && y < cy + ch) {
				child = &c;
			}
		}

		return child ? std::optional<component_ref>{*child} : std::nullopt;
	}

	float box::child_x(const component &child) const
	{
		switch (align()) {
			case box::alignment::center:
			case box::alignment::top_center:
			case box::alignment::bottom_center:
				return x() + 0.5f * (width() - child.width());

			case box::alignment::top_right:
			case box::alignment::center_right:
			case box::alignment::bottom_right:
				return x() + width() - child.width() - border().thickness - padding().right;

			default: return x() + border().thickness + padding().left;
		}
	}

	float box::child_y(const component &child) const
	{
		switch (align()) {
			case box::alignment::center:
			case box::alignment::center_left:
			case box::alignment::center_right:
				return y() + 0.5f * (height() - child.height());

			case box::alignment::bottom_left:
			case box::alignment::bottom_right:
			case box::alignment::bottom_center:
				return y() + height() - child.height() - border().thickness - padding().bottom;

			default: return y() + border().thickness + padding().top;
		}
	}

	float box::child_width(const component &child) const
	{
		const auto p{padding()}, cm{child.margin()};
		return std::max(0.0f, width() - p.left - p.right - cm.left - cm.right - 2.0f * border().thickness);
	}

	float box::child_height(const component &child) const
	{
		const auto p{padding()}, cm{child.margin()};
		return std::max(0.0f, height() - p.top - p.bottom - cm.top - cm.bottom - 2.0f * border().thickness);
	}
}
