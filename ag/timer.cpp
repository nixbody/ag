#include "timer.h"

#include <allegro5/allegro.h>

namespace ag
{
	timer &timer::get(const std::any &native_timer_handle)
	{
		return timers_.at(std::any_cast<ALLEGRO_TIMER *>(native_timer_handle));
	}

	timer::timer(const double tick_interval, event_queue &queue):
		native_handle_{al_create_timer(tick_interval)}
	{
		auto *const t{std::any_cast<ALLEGRO_TIMER *>(native_handle_)};
		timers_.try_emplace(t, *this);
		al_register_event_source(std::any_cast<ALLEGRO_EVENT_QUEUE *>(queue.native_handle_), al_get_timer_event_source(t));
		al_start_timer(t);
	}

	timer::~timer() noexcept
	{
		auto *const t{std::any_cast<ALLEGRO_TIMER *>(native_handle_)};
		al_destroy_timer(t);
		timers_.erase(t);
	}

	timer &timer::pause()
	{
		al_stop_timer(std::any_cast<ALLEGRO_TIMER *>(native_handle_));
		return *this;
	}

	timer &timer::resume()
	{
		al_resume_timer(std::any_cast<ALLEGRO_TIMER *>(native_handle_));
		return *this;
	}

	std::unordered_map<void *, timer &> timer::timers_;
}
