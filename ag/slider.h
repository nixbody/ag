#pragma once

#include "component.h"
#include "events/slider.h"
#include "timer.h"

#include <algorithm>
#include <cmath>

namespace ag
{
	/* Slider component allows to select a value from the given range of values. */
	class slider : public component
	{
	public:
		/* Slider orientation. */
		enum class orientation {horizontal, vertical};

		/* Orientation of this slider. */
		prop<orientation> orientation{orientation::horizontal};

		/* Minimum, maximum, step. */
		prop<double> min{0.0}, max{100.0}, step{1.0};

		/* Track, progress and thumb color. */
		prop<color>
			track_color{[this] { return theme()->slider_track_color(); }},
			progress_color{[this] { return theme()->slider_progress_color(); }},
			thumb_color{[this] { return theme()->slider_thumb_color(); }};

		/* Track and thumb border. */
		prop<ag::border>
			track_border{[this] { return theme()->slider_track_border(); }},
			thumb_border{[this] { return theme()->slider_thumb_border(); }};

		/* Track and thumb dimensions. */
		prop<float>
			track_thickness{[this] { return theme()->slider_track_thickness(); }},
			track_radius{[this] { return theme()->slider_track_radius(); }},
			thumb_width{[this] { return theme()->slider_thumb_width(); }},
			thumb_height{[this] { return theme()->slider_thumb_height(); }},
			thumb_radius{[this] { return theme()->slider_thumb_radius(); }};

		/* Tells whether or not thumb may overlap track borders. */
		prop<bool> thumb_overlaps{[this] { return theme()->slider_thumb_overlaps(); }};

		/* Signal which is emitted when the position of the thumb changes. */
		signal<const events::pos_changed &> on_pos_changed;

		/* Create a new slider. */
		slider()
		{
			pos_timer_.on_ticked([this](const auto &) {
				const auto s{step()};
				change_pos(pos_ + (target_pos_ > pos_ ? s : (target_pos_ < pos_ ? -s : 0.0)));
				if (std::abs(target_pos_ - pos_) < s) pos_timer_.stop();
			});
		}

		/* Current position of the thumb. */
		constexpr double pos() const noexcept
		{ return pos_; }

		/* Change the position of the thumb. */
		slider &change_pos(double new_pos)
		{ return trigger(events::pos_changed{new_pos, *this}); }

		/* Trigger the given event on this component. */
		slider &trigger(const events::pos_changed &event)
		{ event_triggered(event); on_pos_changed.emit(event); return *this; }

	private:
		/* Base interval of the position timer. */
		static constexpr double base_interval{0.002};

		/* Current and target position of the thumb. */
		double pos_{0.0}, target_pos_{pos_};

		/* Position timer. */
		timer pos_timer_{std::chrono::duration<double>(base_interval), false};

		/* Get X coordinate of this slider's track. */
		float track_x() const;

		/* Get Y coordinate of this slider's track. */
		float track_y() const;

		/* Get width of this slider's track. */
		float track_width() const;

		/* Get height of this slider's track. */
		float track_height() const;

		/* Get X coordinate of this slider's thumb center. */
		float thumb_center_x() const;

		/* Get Y coordinate of this slider's thumb center. */
		float thumb_center_y() const;

		/* Draw this slider's track. */
		void draw_track() const;

		/* Draw this slider's progress. */
		void draw_progress() const;

		/* Draw this slider's thumb. */
		void draw_thumb() const;

		/* Draw this slider. */
		void draw_content() const override;

		/* Will be called when the given event was triggered on this slider. */
		virtual void event_triggered(const events::pos_changed &event)
		{ pos_ = std::clamp(event.pos, min(), max()); }

		/* Will be called when the given event was triggered on this component. */
		void event_triggered(const events::mouse_button_pressed &event) override
		{ set_target_pos(event.x, event.y); }

		/* Will be called when the given event was triggered on this component. */
		void event_triggered(const events::mouse_dragged &event) override
		{ set_target_pos(event.x, event.y); }

		/* Will be called when the given event was triggered on this component. */
		void event_triggered(const events::character_typed &event) override
		{
			const auto o{orientation()};
			if (o == orientation::horizontal && event.key.is_right()) change_pos(pos_ + step());
			else if (o == orientation::horizontal && event.key.is_left()) change_pos(pos_ - step());
			else if (o == orientation::vertical && event.key.is_up()) change_pos(pos_ + step());
			else if (o == orientation::vertical && event.key.is_down()) change_pos(pos_ - step());
		}

		/* Set the target position. */
		slider &set_target_pos(double x, double y)
		{
			const auto tr_x{track_x()}, tr_y{track_y()}, tr_w{track_width()}, tr_h{track_height()};
			const auto s{step()}, min_pos{min()}, max_pos{max()}, length{max_pos - min_pos};
			double p{0.0};
			switch (orientation()) {
				case orientation::horizontal: p = x >= tr_x + s ? length * (x - tr_x) / tr_w : min_pos; break;
				case orientation::vertical: p = y <= tr_y + tr_h - s ? max_pos - length * (y - tr_y) / tr_h : min_pos; break;
			}

			target_pos_ = std::clamp(p - std::fmod(p, s), min_pos, max_pos);
			if (s < 0.01) pos_ = target_pos_;
			else if (std::abs(target_pos_ - pos_) >= s) pos_timer_.set_tick_interval(base_interval * s).start();

			return *this;
		}
	};
}
