#include "ripple.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

namespace ag::animations
{
	void ripple::draw_frame() const
	{
		al_draw_filled_circle(x_, y_, current_radius_, al_map_rgba(color_->r, color_->g, color_->b, color_->a));
	}
}
