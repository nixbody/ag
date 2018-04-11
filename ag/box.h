#pragma once

#include "component.h"

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
			/* Children alignment. */
			enum class alignment {
				top_left, top_center, top_right, center_left, center, center_right, bottom_left, bottom_center, bottom_right
			};

			/* Children alignment. */
			prop<alignment> align{alignment::top_left};

			/* Whether or not box should adjust its children width. */
			prop<bool> adjust_children_width{true};

			/* Whether or not box should adjust its children height. */
			prop<bool> adjust_children_height{true};
		};

		/* Destructor. */
		~box() override;

		/* Add the given component into this box. */
		template <typename T>
		box &add(T &&child);

		/* Add the given component into this box. */
		template <typename T, typename Function>
		box &add(T &&child, const Function &setup);

		/* Get style of this box. */
		style_type &style() override;

		/* Get style of this box. */
		const style_type &style() const override;

		/* Draw this box with all its children on the screen. */
		void draw() const override;

		/* Get topmost visible child at the given position. */
		std::optional<child_ref> child_at_pos(const float x, const float y) const;

		/* Get components inside this box. */
		const std::vector<child_ref> &children() const;

	protected:
		/* Will be called when a component is added into this box. */
		virtual void child_added(component &child);

		/* Get supposed X coordinate of the given child. */
		virtual float child_x(const component &child) const;

		/* Get supposed Y coordinate of the given child. */
		virtual float child_y(const component &child) const;

		/* Get supposed width of the given child. */
		virtual float child_width(const component &child) const;

		/* Get supposed height of the given child. */
		virtual float child_height(const component &child) const;

	private:
		/* Style of this box. */
		style_type style_;

		/* Components inside this box. */
		std::vector<child_ref> children_;
	};

	template <typename T>
	box &box::add(T &&child)
	{
		children_.emplace_back(*(new T{std::forward<T>(child)}));
		children_.back().get().parent_ = *this;
		child_added(children_.back().get());
		return *this;
	}

	template <typename T, typename Function>
	box &box::add(T &&child, const Function &setup)
	{
		setup(static_cast<T &>(add(std::forward<T>(child)).children_.back().get()));
		return *this;
	}
}
