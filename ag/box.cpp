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

	void box::draw()
	{
		component::draw();
		for (auto *const c : children_) c->draw();
	}

	std::optional<box::child_ref> box::child_at_pos(const float x, const float y) const
	{
		component *child = nullptr;
		for (auto *const c : children_) {
			const auto &s = c->style();
			const auto cx = s.x(), cy = s.y(), cw = s.width(), ch = s.height();

			if (const auto *const cb = dynamic_cast<box *>(c)) {
				if (const auto &cbc = cb->child_at_pos(x, y)) {
					child = &cbc->get();
					continue;
				}
			}

			if (x >= cx && x < cx + cw && y >= cy && y < cy + ch) {
				child = c;
			}
		}

		return child ? std::optional<box::child_ref>{*child} : std::optional<box::child_ref>{};
	}

	void box::child_added(component &child)
	{
		auto &cs = child.style();
		cs.x = [this] { auto &s = style(); return s.x() + s.padding().right + s.border().thickness; };
		cs.y = [this] { auto &s = style(); return s.y() + s.padding().top + s.border().thickness; };
		cs.width = [this] { auto &s = style(); return s.width() - s.padding().left - s.border().thickness; };
		cs.height = [this] { auto &s = style(); return s.height() - s.padding().bottom - s.border().thickness; };
		cs.text_font = [this] { return style().text_font(); };
		cs.text_color = [this] { return style().text_color(); };
		cs.text_align = [this] { return style().text_align(); };
		cs.line_height = [this] { return style().line_height(); };
	}
}
