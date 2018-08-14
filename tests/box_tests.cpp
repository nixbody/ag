#include "../ag/box.h"
#include "../ag/label.h"

#include "catch.hpp"

SCENARIO("Adding children into a box", "[box]")
{
	GIVEN("we have a box and some components")
	{
		ag::box box;
		box.x = box.y = 0.0f; box.width = 800.0f; box.height = 600.0f; box.line_height = 32.0f;
		box.text_color = {1, 2, 3}; box.text_align = ag::font::alignment::center;

		WHEN("we add those components into the box")
		{
			box
				.add<ag::label>([](auto &c) { c.text = "Child 1"; })
				.add<ag::label>([](auto &c) { c.text = "Child 2"; })
				.add<ag::label>();

			THEN("the box has corresponding number of children")
			{
				REQUIRE(box.children().size() == 3);
			}

			THEN("the box keeps the order in which the children were added")
			{
				REQUIRE(box.children()[0].get().text() == "Child 1");
				REQUIRE(box.children()[1].get().text() == "Child 2");
				REQUIRE(box.children()[2].get().text().empty());
			}

			THEN("children inherit position, size and text style from parent box")
			{
				for (const ag::component &child : box.children()) {
					REQUIRE(child.x() == box.x());
					REQUIRE(child.y() == box.y());
					REQUIRE(child.width() == box.width());
					REQUIRE(child.height() == box.height());
					REQUIRE(child.line_height() == box.line_height());
					REQUIRE(child.text_color() == box.text_color());
					REQUIRE(child.text_align() == box.text_align());
				}
			}
		}
		AND_WHEN("we ask if there is a child component on given position")
		{
			box
				.add<ag::label>([](auto &c) { c.text = "Child 1"; c.x = 5.0f; c.y = 5.0f; c.width = 5.0f; c.height = 5.0f; })
				.add<ag::label>([](auto &c) { c.text = "Child 2"; c.x = 9.0f; c.y = 9.0f; c.width = 5.0f; c.height = 5.0f; })
				.add<ag::label>([](auto &c) { c.text = "Child 3"; c.x = 9.0f; c.y = 9.0f; c.width = 5.0f; c.height = 5.0f; });

			const auto &c1{box.child_at_pos(5.0f, 5.0f)}, c2{box.child_at_pos(13.0f, 13.0f)};

			THEN("the box can tell")
			{
				REQUIRE(!box.child_at_pos(0.0f, 0.0f));
				REQUIRE((c1 && c1->get().text() == "Child 1"));
			}
			AND_THEN("components added latter hide components underneath")
			{
				REQUIRE((c2 && c2->get().text() == "Child 3"));
			}
			AND_THEN("only visible components are considered")
			{
				c2->get().visible = false;
				REQUIRE(box.child_at_pos(13.0f, 13.0f)->get().text() == "Child 2");
			}
		}
		AND_WHEN("the box is not visible")
		{
			box.visible = false;

			THEN("its children are considered invisible too")
			{
				box.add<ag::label>([](auto &c) { c.x = c.y = 1.0f; });
				REQUIRE(!box.child_at_pos(1.0f, 1.0f));
			}
		}
		AND_WHEN("we ask for a child on a position outside its parent region")
		{
			THEN("nullopt is returned")
			{
				box.add<ag::label>([](auto &c) { c.x = c.y = 9999.0f; });
				REQUIRE(!box.child_at_pos(9999.0f, 9999.0f));
			}
		}
	}
}

SCENARIO("Children sizing", "[box]")
{
	GIVEN("a box with children")
	{
		ag::box box;
		box.x = box.y = 0.0f; box.width = box.height = 10.0f; box.padding = 10.0f;
		box.add<ag::label>();

		WHEN("the box calculates its children size")
		{
			THEN("neither width nor height are ever lower than zero")
			{
				REQUIRE(box.children().front().get().width() == 0.0f);
				REQUIRE(box.children().front().get().height() == 0.0f);
			}
		}
	}
}

SCENARIO("Children are aligned according to their parent box alignment setting", "[box]")
{
	ag::box box;
	box.x = box.y = 0.0f; box.width = box.height = 20.0f;
	box.add<ag::label>([](auto &c) { c.width = c.height = 10.0f; });

	GIVEN("the box alignment is set to a certain value")
	{
		WHEN("children positions are calculated by the box")
		{
			THEN("the resulting coordinates correspond to the set alignment")
			{
				box.align = ag::box::alignment::top_left;
				REQUIRE(box.children().front().get().x() == 0.0f);
				REQUIRE(box.children().front().get().y() == 0.0f);

				box.align = ag::box::alignment::top_center;
				REQUIRE(box.children().front().get().x() == 5.0f);
				REQUIRE(box.children().front().get().y() == 0.0f);

				box.align = ag::box::alignment::top_right;
				REQUIRE(box.children().front().get().x() == 10.0f);
				REQUIRE(box.children().front().get().y() == 0.0f);

				box.align = ag::box::alignment::center_left;
				REQUIRE(box.children().front().get().x() == 0.0f);
				REQUIRE(box.children().front().get().y() == 5.0f);

				box.align = ag::box::alignment::center;
				REQUIRE(box.children().front().get().x() == 5.0f);
				REQUIRE(box.children().front().get().y() == 5.0f);

				box.align = ag::box::alignment::center_right;
				REQUIRE(box.children().front().get().x() == 10.0f);
				REQUIRE(box.children().front().get().y() == 5.0f);

				box.align = ag::box::alignment::bottom_left;
				REQUIRE(box.children().front().get().x() == 0.0f);
				REQUIRE(box.children().front().get().y() == 10.0f);

				box.align = ag::box::alignment::bottom_center;
				REQUIRE(box.children().front().get().x() == 5.0f);
				REQUIRE(box.children().front().get().y() == 10.0f);

				box.align = ag::box::alignment::bottom_right;
				REQUIRE(box.children().front().get().x() == 10.0f);
				REQUIRE(box.children().front().get().y() == 10.0f);
			}
		}
	}
}
