#include "../ag/prop.h"
#include "../ag/color.h"

#include "catch.hpp"
#include <cstdint>
#include <string>
#include <string_view>

SCENARIO("Properties can be created easily from values", "[prop]")
{
	GIVEN("values are simple primitives")
	{
		WHEN("properties are initialized directly from them")
		{
			ag::prop<int> int_prop{123};
			ag::prop<float> float_prop{3.14f};
			ag::prop<bool> bool_prop{true};

			THEN("properties return them")
			{
				REQUIRE(int_prop() == 123);
				REQUIRE(float_prop() == 3.14f);
				REQUIRE(bool_prop() == true);
			}
		}

		WHEN("properties are copy-initialized from them")
		{
			ag::prop<int> int_prop = 123;
			ag::prop<float> float_prop = 3.14f;
			ag::prop<bool> bool_prop = true;

			THEN("properties return them")
			{
				REQUIRE(int_prop() == 123);
				REQUIRE(float_prop() == 3.14f);
				REQUIRE(bool_prop() == true);
			}
		}

		WHEN("they are assigned to properties")
		{
			ag::prop<int> int_prop;
			ag::prop<float> float_prop;
			ag::prop<bool> bool_prop;

			int_prop = 123;
			float_prop = 3.14f;
			bool_prop = true;

			THEN("properties return them")
			{
				REQUIRE(int_prop() == 123);
				REQUIRE(float_prop() == 3.14f);
				REQUIRE(bool_prop() == true);
			}
		}
	}

	GIVEN("values are complex objects")
	{
		WHEN("properties are initialized directly from them")
		{
			ag::prop<std::string> string_prop{"Hello!"};
			ag::prop<ag::color> color_prop{1, 2, 3};

			THEN("properties return them")
			{
				REQUIRE(string_prop() == "Hello!");
				REQUIRE(color_prop() == ag::color{1, 2, 3});
			}
		}

		WHEN("properties are copy-initialized from them")
		{
			ag::prop<std::string> string_prop = "Hello!";
			ag::prop<ag::color> color_prop = {1, 2, 3};

			THEN("properties return them")
			{
				REQUIRE(string_prop() == "Hello!");
				REQUIRE(color_prop() == ag::color{1, 2, 3});
			}
		}

		WHEN("they are assigned to properties")
		{
			ag::prop<std::string> string_prop;
			ag::prop<ag::color> color_prop;

			string_prop = "Hello!";
			color_prop = {1, 2, 3};

			THEN("properties return them")
			{
				REQUIRE(string_prop() == "Hello!");
				REQUIRE(color_prop() == ag::color{1, 2, 3});
			}
		}

		WHEN("values are of type std::string_view")
		{
			const char str[]{"Hello!"};
			ag::prop<std::string_view> p{str};

			THEN("properties create a string copy of that view which they are owners of")
			{
				REQUIRE(p() == str);
				REQUIRE(reinterpret_cast<std::intptr_t>(p().data()) != reinterpret_cast<std::intptr_t>(str));
			}
		}
	}
}
