#include "../../start.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

namespace ag
{
	int start(const std::function<void ()> &set_up)
	{
		al_init();
		al_install_keyboard();
		al_install_mouse();
		al_init_font_addon();
		al_init_ttf_addon();
		al_init_primitives_addon();

		set_up();

		return 0;
	}
}
