#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "../ag/button.h"
#include "../ag/display.h"
#include "../ag/resources.h"
#include "../ag/start.h"
#include "../ag/theme.h"

namespace ag
{
	struct material_theme : theme
	{
		/* Background color. */
		color bg_color() const noexcept override
		{ return {255, 255, 255}; }

		/* Text font. */
		font text_font() const override
		{ return {resources::roboto_regular_woff(), 14}; }

		/* Text color. */
		color text_color() const noexcept override
		{ return {0, 0, 0}; }

		/* Line height. */
		float line_height() const noexcept override
		{ return 0.0f; }

		/* Button radius. */
		float button_radius() const noexcept override
		{ return 3.0f; }

		/* Button padding. */
		insets button_padding() const noexcept override
		{ return {9.5f, 15.5f}; }

		/* Button font. */
		font button_font() const override
		{ return {resources::roboto_medium_woff(), 14}; }

		/* Button primary color. */
		color button_primary_color() const noexcept override
		{ return {33, 150, 243}; }

		/* Button secondary color. */
		color button_secondary_color() const noexcept override
		{ return {255, 255, 255}; }
	};
}

int main(int argc, char *argv[])
{
	Catch::Session().run(argc, argv);

	return ag::start([] {
		ag::set_theme(ag::material_theme{});

		ag::display display{1280, 800, "Ag Demo"};
		ag::box scene;

		scene.align = ag::box::alignment::center;
		scene.add<ag::button>([](auto &c) {
			c.text = "Hello!";
		});

		display.on_closed(std::bind(std::exit, 0));
		display.draw(scene);
		ag::run_event_loop();
	});
}
