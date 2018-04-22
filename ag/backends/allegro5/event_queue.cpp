#include "../../event_queue.h"
#include "../../timer.h"

#include <allegro5/allegro.h>
#include <memory>

namespace ag
{
	event_queue::event_queue():
		native_handle_{al_create_event_queue()},
		async_event_source_native_handle_{new ALLEGRO_EVENT_SOURCE}
	{
		al_register_event_source(std::any_cast<ALLEGRO_EVENT_QUEUE *>(native_handle_), al_get_mouse_event_source());
		al_register_event_source(std::any_cast<ALLEGRO_EVENT_QUEUE *>(native_handle_), al_get_keyboard_event_source());
		al_init_user_event_source(std::any_cast<ALLEGRO_EVENT_SOURCE *>(async_event_source_native_handle_));
		al_register_event_source(
			std::any_cast<ALLEGRO_EVENT_QUEUE *>(native_handle_),
			std::any_cast<ALLEGRO_EVENT_SOURCE *>(async_event_source_native_handle_)
		);
	}

	event_queue::~event_queue()
	{
		al_destroy_event_queue(std::any_cast<ALLEGRO_EVENT_QUEUE *>(native_handle_));
		al_destroy_user_event_source(std::any_cast<ALLEGRO_EVENT_SOURCE *>(async_event_source_native_handle_));
		delete std::any_cast<ALLEGRO_EVENT_SOURCE *>(async_event_source_native_handle_);
	}

	void event_queue::wait_for_events() const
	{
		static const auto async_event_type = ALLEGRO_GET_EVENT_TYPE('A', 'S', 'Y', 'N');

		auto *const queue = std::any_cast<ALLEGRO_EVENT_QUEUE *>(native_handle_);
		ALLEGRO_EVENT e;
		for (;;) {
			al_wait_for_event(queue, &e);
			switch (e.type) {
				case async_event_type:
					(*std::unique_ptr<std::function<void ()>>{reinterpret_cast<std::function<void ()> *>(e.user.data1)})();
					break;

				case ALLEGRO_EVENT_TIMER:
					{
						auto &timer = timer::get(e.timer.source);
						timer.on_ticked.emit(events::timer_ticked{e.timer.count, timer});
					}
					break;
			}
			on_event_occured.emit(e);
		}
	}

	void event_queue::run_later(std::function<void ()> runner) const
	{
		static const auto async_event_type = ALLEGRO_GET_EVENT_TYPE('A', 'S', 'Y', 'N');

		ALLEGRO_EVENT e;
		e.user.type = async_event_type;
		e.user.data1 = reinterpret_cast<intptr_t>(new std::function<void ()>{std::move(runner)});
		al_emit_user_event(std::any_cast<ALLEGRO_EVENT_SOURCE *>(async_event_source_native_handle_), &e, nullptr);
	}

	event_queue &default_event_queue()
	{
		static event_queue queue;
		return queue;
	}

	void run_later(std::function<void ()> runner, const event_queue &queue)
	{
		queue.run_later(std::move(runner));
	}
}
