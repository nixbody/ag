#include "../ag/box.h"
#include "../ag/button.h"
#include "../ag/display.h"
#include "../ag/start.h"

#include "../ag/backends/default.h"

int main(int argc, char *argv[])
{
	return ag::start([] {

		ag::display display{800, 600, "Ag Demo"}, dialog{320, 200, "Dialog"};
		auto &scene{display.scene()};

		scene.border = {1.0f, ag::color{255, 0, 0}};
		scene.text = "The last example of this demo show how to use an upload button.";

		scene.align = ag::box::alignment::center;
		scene.text_align = ag::font::alignment::center;
		scene.add<ag::button>([](auto &c) {
			c.text = "Hello!";
			c.on_double_clicked([](auto &e) { e.target.text = "Clicked!"; e.target.display().set_maximized(!e.target.display().maximized()); });
		});

		display.on_closed(std::bind(std::exit, 0));
		display.show_centered();
		dialog.show_centered(display);
		ag::run_event_loop();
	});
}
