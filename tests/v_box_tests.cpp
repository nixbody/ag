#include "../ag/v_box.h"
#include "../ag/label.h"

#include "catch.hpp"

SCENARIO("Children are aligned according to their parent v_box alignment setting", "[v_box]")
{
	ag::v_box box;
	box.x = box.y = 0.0f; box.width = box.height = 20.0f;
	box.add<ag::label>([](auto &c) { c.width = c.height = 5.0f; });
	box.add<ag::label>([](auto &c) { c.width = c.height = 5.0f; });

	GIVEN("the box alignment is set to a certain value")
	{
		WHEN("children positions are calculated by the box")
		{
			THEN("the resulting coordinates correspond to the set alignment")
			{
				box.align = ag::box::alignment::top_left;
				REQUIRE(box.children().front().get().x() == 0.0f);
				REQUIRE(box.children().front().get().y() == 0.0f);
				REQUIRE(box.children().back().get().x() == 0.0f);
				REQUIRE(box.children().back().get().y() == 5.0f);

				box.align = ag::box::alignment::top_center;
				REQUIRE(box.children().front().get().x() == 7.5f);
				REQUIRE(box.children().front().get().y() == 0.0f);
				REQUIRE(box.children().back().get().x() == 7.5f);
				REQUIRE(box.children().back().get().y() == 5.0f);

				box.align = ag::box::alignment::top_right;
				REQUIRE(box.children().front().get().x() == 15.0f);
				REQUIRE(box.children().front().get().y() == 0.0f);
				REQUIRE(box.children().back().get().x() == 15.0f);
				REQUIRE(box.children().back().get().y() == 5.0f);

				box.align = ag::box::alignment::center_left;
				REQUIRE(box.children().front().get().x() == 0.0f);
				REQUIRE(box.children().front().get().y() == 5.0f);
				REQUIRE(box.children().back().get().x() == 0.0f);
				REQUIRE(box.children().back().get().y() == 10.0f);

				box.align = ag::box::alignment::center;
				REQUIRE(box.children().front().get().x() == 7.5f);
				REQUIRE(box.children().front().get().y() == 5.0f);
				REQUIRE(box.children().back().get().x() == 7.5f);
				REQUIRE(box.children().back().get().y() == 10.0f);

				box.align = ag::box::alignment::center_right;
				REQUIRE(box.children().front().get().x() == 15.0f);
				REQUIRE(box.children().front().get().y() == 5.0f);
				REQUIRE(box.children().back().get().x() == 15.0f);
				REQUIRE(box.children().back().get().y() == 10.0f);

				box.align = ag::box::alignment::bottom_left;
				REQUIRE(box.children().front().get().x() == 0.0f);
				REQUIRE(box.children().front().get().y() == 10.0f);
				REQUIRE(box.children().back().get().x() == 0.0f);
				REQUIRE(box.children().back().get().y() == 15.0f);

				box.align = ag::box::alignment::bottom_center;
				REQUIRE(box.children().front().get().x() == 7.5f);
				REQUIRE(box.children().front().get().y() == 10.0f);
				REQUIRE(box.children().back().get().x() == 7.5f);
				REQUIRE(box.children().back().get().y() == 15.0f);

				box.align = ag::box::alignment::bottom_right;
				REQUIRE(box.children().front().get().x() == 15.0f);
				REQUIRE(box.children().front().get().y() == 10.0f);
				REQUIRE(box.children().back().get().x() == 15.0f);
				REQUIRE(box.children().back().get().y() == 15.0f);
			}
		}
	}
}
