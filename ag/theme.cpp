#include "theme.h"

namespace ag
{
	const theme *theme::current_{nullptr};

	const theme &get_theme()
	{
		return *theme::current_;
	}
}
