#include "box.h"

namespace ag
{
	box::~box()
	{
		for (const auto *const c : children_) delete c;
	}

	box::style_type &box::style()
	{
		return style_;
	}

	const box::style_type &box::style() const
	{
		return style_;
	}

	void box::draw() const
	{
		if (!style().visible()) return;

		component::draw();
		for (auto *const c : children_) c->draw();
	}

	std::optional<box::child_ref> box::child_at_pos(const float x, const float y) const
	{
		component *child = nullptr;
		for (auto *const c : children_) {
			const auto &s = c->style();
			const auto v = s.visible();
			const auto cx = s.x(), cy = s.y(), cw = s.width(), ch = s.height();

			if (const auto *const cb = dynamic_cast<box *>(c)) {
				if (const auto &cbc = cb->child_at_pos(x, y)) {
					child = &cbc->get();
					continue;
				}
			}

			if (v && x >= cx && x < cx + cw && y >= cy && y < cy + ch) {
				child = c;
			}
		}

		return child ? std::optional<box::child_ref>{*child} : std::optional<box::child_ref>{};
	}

	void box::child_added(component &child)
	{
		auto &cs = child.style();
		cs.visible = [this] { return style().visible(); };
		cs.x = [this, &child] { return child_x(child); };
		cs.y = [this, &child] { return child_y(child); };
		cs.width = [this, &child, w = child.width()] { return style().adjust_children_width() ? child_width(child) : w; };
		cs.height = [this, &child, h = child.height()] { return style().adjust_children_height() ? child_height(child) : h; };
		cs.text_font = [this] { return style().text_font(); };
		cs.text_color = [this] { return style().text_color(); };
		cs.text_align = [this] { return style().text_align(); };
		cs.line_height = [this] { return style().line_height(); };
	}

	float box::child_x(const component &child) const
	{
		using a = box::style_type::alignment;

		const auto &s = style();
		const auto p = s.padding();

		switch (s.align()) {
			case a::center:
			case a::top_center:
			case a::bottom_center:
				return s.x() + 0.5f * (s.width() - child.style().width());

			case a::top_right:
			case a::center_right:
			case a::bottom_right:
				return s.x() + s.width() - child.style().width() - s.border().thickness - p.right;

			default: return s.x() + s.border().thickness + p.left;
		}
	}

	float box::child_y(const component &child) const
	{
		using a = box::style_type::alignment;

		const auto &s = style();
		const auto p = s.padding();

		switch (s.align()) {
			case a::center:
			case a::center_left:
			case a::center_right:
				return s.y() + 0.5f * (s.height() - child.style().height());

			case a::bottom_left:
			case a::bottom_right:
			case a::bottom_center:
				return s.y() + s.height() - child.style().height() - s.border().thickness - p.bottom;

			default: return s.y() + s.border().thickness + p.top;
		}
	}

	float box::child_width(const component &child) const
	{
		auto &s = style();
		const auto p = s.padding(), cm = child.style().margin();
		return s.width() - p.left - p.right - cm.left - cm.right - 2.0f * s.border().thickness;
	}

	float box::child_height(const component &child) const
	{
		auto &s = style();
		const auto p = s.padding(), cm = child.style().margin();
		return s.height() - p.top - p.bottom - cm.top - cm.bottom - 2.0f * s.border().thickness;
	}
}
