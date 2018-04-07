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
		child.style().x = [this] { return style().x() + style().padding().right + style().border().thickness; };
		child.style().y = [this] { return style().y() + style().padding().top + style().border().thickness; };
		child.style().width = [this] { return style().width() - style().padding().left - style().border().thickness; };
		child.style().height = [this] { return style().height() - style().padding().bottom - style().border().thickness; };
		child.style().text_font = [this] { return style().text_font(); };
	}
}
