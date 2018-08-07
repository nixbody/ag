#include "../../slider.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

namespace ag
{
	float slider::track_x() const
	{
		if (orientation() == orientation::vertical) return x() + 0.5f * (width() - track_width());
		return thumb_overlaps()
			? x() + border().thickness + padding().left + 0.5f * thumb_width() + 1.0f
			: x() + border().thickness + padding().left + 1.0f;
	}

	float slider::track_y() const
	{
		if (orientation() == orientation::horizontal) return y() + 0.5f * (height() - track_height());
		return thumb_overlaps()
			? y() + border().thickness + padding().top + 0.5f * thumb_height() + 1.0f
			: y() + border().thickness + padding().top + 1.0f;
	}

	float slider::track_width() const
	{
		if (orientation() == orientation::vertical) return track_thickness();
		return thumb_overlaps()
			? width() - padding().left - padding().right - 2.0f * border().thickness - thumb_width() - 2.0f
			: width() - padding().left - padding().right - 2.0f * border().thickness - 2.0f;
	}

	float slider::track_height() const
	{
		if (orientation() == orientation::horizontal) return track_thickness();
		return thumb_overlaps()
			? height() - padding().top - padding().bottom - 2.0f * border().thickness - thumb_height() - 2.0f
			: height() - padding().top - padding().bottom - 2.0f * border().thickness - 2.0f;
	}

	float slider::thumb_center_x() const
	{
		if (orientation() == orientation::vertical) return x() + 0.5f * width();
		const float tr_x{track_x()}, tr_w{track_width()}, th_w{thumb_width()}, th_x(tr_x + tr_w / ((max() - min()) / pos_));
		return thumb_overlaps() ? th_x : std::clamp(th_x, tr_x + 0.5f * th_w, tr_x + tr_w - 0.5f * th_w);
	}

	float slider::thumb_center_y() const
	{
		if (orientation() == orientation::horizontal) return y() + 0.5f * height();
		const float tr_y{track_y()}, tr_h{track_height()}, th_h{thumb_height()};
		const float th_y(tr_y + (tr_h - tr_h / ((max() - min()) / pos_)));
		return thumb_overlaps() ? th_y : std::clamp(th_y, tr_y + 0.5f * th_h, tr_y + tr_h - 0.5f * th_h);
	}

	void slider::draw_track() const
	{
		const auto tr_w{track_width()}, tr_h{track_height()};
		if (tr_w <= 0.0f || tr_h <= 0.0f) return;

		const auto trb{track_border()};
		const auto trr{track_radius()};
		const auto trc{track_color()};

		if (trb.thickness > 0.0f && trb.color.a) {
			const auto trb_x{track_x() + 0.5f * trb.thickness}, trb_y{track_y() + 0.5f * trb.thickness};
			al_draw_rounded_rectangle(
				trb_x, trb_y, trb_x + tr_w - trb.thickness, trb_y + tr_h - trb.thickness,
				trr, trr, al_map_rgba(trb.color.r, trb.color.g, trb.color.b, trb.color.a), trb.thickness
			);
		}

		if (trc.a) {
			const auto tr_x{track_x() + trb.thickness}, tr_y{track_y() + trb.thickness};
			al_draw_filled_rounded_rectangle(
				tr_x, tr_y, tr_x + tr_w - 2.0f * trb.thickness, tr_y + tr_h - 2.0f * trb.thickness,
				trr, trr, al_map_rgba(trc.r, trc.g, trc.b, trc.a)
			);
		}
	}

	void slider::draw_progress() const
	{
		const auto tr_w{track_width()}, tr_h{track_height()};
		if (tr_w <= 0.0f || tr_h <= 0.0f) return;

		const auto trb{track_border()};
		const auto trr{track_radius()};
		const auto pgc{progress_color()};

		if (pgc.a) {
			const auto tr_x{track_x() + trb.thickness}, tr_y{track_y() + trb.thickness};
			const auto vert{orientation() == orientation::vertical};
			const auto x2{vert ? tr_x + tr_w - 2.0f * trb.thickness : thumb_center_x()};
			const auto y1{vert ? tr_y + tr_h : tr_y};
			const auto y2{vert ? thumb_center_y() : tr_y + tr_h - 2.0f * trb.thickness};
			al_draw_filled_rounded_rectangle(tr_x, y1, x2, y2, trr, trr, al_map_rgba(pgc.r, pgc.g, pgc.b, pgc.a));
		}
	}

	void slider::draw_thumb() const
	{
		const auto th_h{thumb_height()}, th_w{thumb_width()};
		if (th_w <= 0.0f || th_h <= 0.0f) return;

		const auto thr{thumb_radius()}, th_x{thumb_center_x()}, th_y{thumb_center_y()};
		const auto thb{thumb_border()};
		const auto thc{thumb_color()};

		if (thb.thickness > 0.0f && thb.color.a) {
			al_draw_rounded_rectangle(
				th_x - 0.5f * th_w, th_y - 0.5f * th_h,
				th_x + 0.5f * th_w, th_y + 0.5f * th_h,
				thr, thr, al_map_rgba(thb.color.r, thb.color.g, thb.color.b, thb.color.a), thb.thickness
			);
		}

		if (thc.a) {
			al_draw_filled_rounded_rectangle(
				th_x - 0.5f * (th_w - thb.thickness), th_y - 0.5f * (th_h - thb.thickness),
				th_x + 0.5f * (th_w - thb.thickness), th_y + 0.5f * (th_h - thb.thickness),
				thr, thr, al_map_rgba(thc.r, thc.g, thc.b, thc.a)
			);
		}
	}

	void slider::draw_content() const
	{
		draw_track();
		draw_progress();
		draw_thumb();
	}
}
