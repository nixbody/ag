#include "insets.h"

namespace ag
{
	insets::insets(const float all): top{all}, right{all}, bottom{all}, left{all}
	{}

	insets::insets(const float top_bottom, const float right_left):
		top{top_bottom}, right{right_left}, bottom{top_bottom}, left{right_left}
	{}

	insets::insets(const float top, const float right, const float bottom, const float left):
		top{top}, right{right}, bottom{bottom}, left{left}
	{}
}
