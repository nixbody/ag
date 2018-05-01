#include "../ag/signal.h"

#include "catch.hpp"

SCENARIO("Connected slots listen to their signals", "[signal]")
{
	ag::signal<int, int> sig;

	GIVEN("a slot is connected")
	{
		bool invoked{false};
		int invoked_with[]{0, 0};

		auto conn = sig([&invoked, &invoked_with](auto a1, auto a2) {
			invoked = true;
			invoked_with[0] = a1;
			invoked_with[1] = a2;
		});

		WHEN("the signal to which the slot is connected is emitted")
		{
			sig.emit(123, 999);

			THEN("the slot is invoked")
			{
				REQUIRE(invoked == true);
			}
			AND_THEN("all arguments are passed to the slot")
			{
				REQUIRE(invoked_with[0] == 123);
				REQUIRE(invoked_with[1] == 999);
			}
		}

		WHEN("the slot is disconnected and the signal is emitted")
		{
			sig.disconnect(conn);
			sig.emit(123, 999);

			THEN("the slot is no longer invoked")
			{
				REQUIRE(invoked == false);
				REQUIRE(invoked_with[0] == 0);
				REQUIRE(invoked_with[1] == 0);
			}
		}
	}
}
