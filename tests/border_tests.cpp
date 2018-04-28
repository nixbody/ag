#include "../ag/border.h"

#include "catch.hpp"

SCENARIO("Borders are constructed correcly", "[border]")
{
	GIVEN("a border with certain thickness and color")
	{
		WHEN("the thickness and color are passed to the border constructor")
		{
			ag::border border{2.5f, {1, 2, 3}};

			THEN("the resulting border actually has these attributes")
			{
				REQUIRE(border.thickness == 2.5f);
				REQUIRE(border.color == ag::color{1, 2, 3});
			}
		}
	}
}
