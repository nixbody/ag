#pragma once

#include "component.h"
#include "theme.h"

#include <string>
#include <utility>

namespace ag
{
	/* Text label. */
	class label : public component
	{
	public:
		/* Label style. */
		struct style_type : component::style_type
		{};

		/* Create a new label with the given text. */
		template <typename T>
		label(T &&text);

		/* Set this label's text. */
		template <typename T>
		label &set_text(T &&text);

		/* Get this label's text. */
		const std::string &text() const;

		/* Get style of this label. */
		style_type &style() override;

		/* Get style of this label. */
		const style_type &style() const override;

		/* Draw this label. */
		void draw() const override;

	private:
		/* This label's text. */
		std::string text_;

		/* Style of this label. */
		style_type style_;
	};

	template <typename T>
	label::label(T &&text): text_{std::forward<T>(text)}
	{}

	template <typename T>
	label &label::set_text(T &&text)
	{
		text_ = std::forward<T>(text);
		return *this;
	}
}
