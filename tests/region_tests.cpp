#include "../ag/label.h"
#include "../ag/region.h"

#include "catch.hpp"

SCENARIO("Regions testing", "[region]")
{
	GIVEN("a manually defined region")
	{
		ag::region reg{0.0f, 0.0f, 800.0f, 600.0f};

		WHEN("we ask the region if it contains given coordinates")
		{
			THEN("the region can tell")
			{
				REQUIRE(reg.contains(9999.0f, 9999.0f) == false);
				REQUIRE(reg.contains(0.0f, 0.0f) == true);
			}
		}
	}

	GIVEN("a region defined by a component")
	{
		ag::label label; label.x = label.y = 0.0f; label.width = label.height = 100.0f;
		ag::region reg{label};

		WHEN("we ask the region if it contains given coordinates")
		{
			THEN("the region can tell")
			{
				REQUIRE(reg.contains(100.0f, 100.0f) == false);
				REQUIRE(reg.contains(0.0f, 0.0f) == true);
			}
		}
	}
}
