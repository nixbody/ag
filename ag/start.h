#pragma once

#include <functional>

namespace ag
{
	/* Initialize the library and run the given function. */
	int start(const std::function<void ()> &set_up);
}
