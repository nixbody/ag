#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "../ag/start.h"
#include "../ag/backends/default.h"

int main(int argc, char *argv[])
{
	ag::start([] {});
	const auto result{Catch::Session().run(argc, argv)};
	system("PAUSE");
	return result;
}
