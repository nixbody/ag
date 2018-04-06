#pragma once

#include "component.h"
#include "theme.h"

#include <functional>
#include <optional>
#include <utility>
#include <vector>

namespace ag
{
	/* Component box. */
	class box : public component
	{
	public:
		/* Child reference type. */
		using child_ref = std::reference_wrapper<component>;

		/* Box style. */
		struct style_type : component::style_type
		{
			/* Font for items inside this box. */
			prop<font> font{get_theme().font};
		};

		/* Destructor. */
		~box() override;

		/* Add the given component into this box. */
		template <typename T>
		box &add(T &&child);

		/* Add the given component into this box. */
		template <typename T>
		box &add(T &&child, const std::function<void (component &)> &setup);

		/* Get style of this box. */
		inline style_type &style() override;

		/* Draw this box with all its children on the screen. */
		void draw() override;

		/* Get topmost child at the given position. */
		std::optional<child_ref> child_at_pos(const float x, const float y) const;

	protected:
		/* Will be called when a component is added into this box. */
		virtual void child_added(component &child);

	private:
		/* Style of this box. */
		style_type style_;

		/* Components inside this box. */
		std::vector<component *> children_;
	};

	template <typename T>
	box &box::add(T &&child)
	{
		children_.emplace_back(new T{std::forward<T>(child)});
		children_.back()->parent_ = *this;
		child_added(*children_.back());
		return *this;
	}

	template <typename T>
	box &box::add(T &&child, const std::function<void (component &)> &setup)
	{
		setup(*add(std::forward<T>(child)).children_.back());
		return *this;
	}
}
