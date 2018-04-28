#include "../ag/color.h"

#include "catch.hpp"

SCENARIO("Colors can be represented in multiple ways", "[color]")
{
	GIVEN("a color is represented by a single number")
	{
		WHEN("this number is a 32-bit integer")
		{
			ag::color color{0x11223344};

			THEN("its bytes (from highest to lowest) represent the following color channels (in that order): ARGB")
			{
				REQUIRE(color.a == 0x11);
				REQUIRE(color.r == 0x22);
				REQUIRE(color.g == 0x33);
				REQUIRE(color.b == 0x44);
			}
		}
		AND_WHEN("alpha is 0")
		{
			THEN("is set to 255")
			{
				REQUIRE(ag::color{0xaabbcc}.a == 255);
			}
		}
	}

	GIVEN("a color is represented by multiple values")
	{
		WHEN("those are 3 bytes (8-bit integers)")
		{
			ag::color color{11, 22, 33};

			THEN("they represent red, green and blue color channels")
			{
				REQUIRE(color.r == 11);
				REQUIRE(color.g == 22);
				REQUIRE(color.b == 33);
			}
			AND_THEN("alpha is always 255")
			{
				REQUIRE(color.a == 255);
			}
		}

		WHEN("those are 4 bytes (8-bit integers)")
		{
			ag::color color{11, 22, 33, 44};

			THEN("they represent red, green, blue and alpha color channels")
			{
				REQUIRE(color.r == 11);
				REQUIRE(color.g == 22);
				REQUIRE(color.b == 33);
				REQUIRE(color.a == 44);
			}
		}
	}
}

SCENARIO("Colors can be compared", "[color]")
{
	GIVEN("we have two colors")
	{
		WHEN("those are equal")
		{
			THEN("the comparison operator should return true")
			{
				REQUIRE(ag::color{1, 2, 3} == ag::color{1, 2, 3, 255});
			}
		}

		WHEN("those are not equal")
		{
			THEN("the comparison operator should return false")
			{
				REQUIRE(ag::color{1, 2, 3} != ag::color{1, 2, 3, 0});
			}
		}
	}

	GIVEN("we have one color and a number representing second color")
	{
		WHEN("those are equal")
		{
			THEN("the comparison operator should return true")
			{
				REQUIRE(ag::color{0x11, 0x22, 0x33} == 0x112233);
			}
		}

		WHEN("those are not equal")
		{
			THEN("the comparison operator should return false")
			{
				REQUIRE(ag::color{0x11, 0x22, 0x33} != 0x667788);
			}
		}
	}
}
