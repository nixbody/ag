#pragma once

#include "component.h"
#include "type_traits.h"

#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace ag
{
	/* Component box. */
	class box : public component
	{
	public:
		/* Inherit component constructors. */
		using component::component;

		/* Children alignment. */
		enum class alignment
		{top_left, top_center, top_right, center_left, center, center_right, bottom_left, bottom_center, bottom_right};

		/* Children alignment. */
		prop<alignment> align{alignment::top_left};

		/* Initialize the newly created box. */
		box()
		{ focusable = false; }

		/* Get topmost visible child at the given position. */
		std::optional<component_ref> child_at_pos(float x, float y) const;

		/* Add a component of the given type into this box and forward the given arguments to its constructor. */
		template <typename Component, typename ... T>
		box &add(T && ... args);

		/* Add a component of the given type into this box and pass it to the given callback. */
		template<typename Component, typename Invocable, typename = enable_if_invocable_t<Invocable, Component &>>
		box &add(Invocable &&set_up)
		{ set_up(static_cast<Component &>(add<Component>().children_refs_.back().get())); return *this; }

		/* Get components stored inside this box. */
		constexpr const std::vector<component_ref> &children() const noexcept
		{ return children_refs_; }

	private:
		/* References to components stored inside this box. */
		std::vector<component_ref> children_refs_;

		/* Components stored inside this box. */
		std::vector<std::unique_ptr<component>> children_;

		/* Draw components stored inside this box. */
		void draw_content() const override
		{ for (const component &c : children_refs_) c.draw(); }

		/* Get supposed X coordinate of the given child. */
		virtual float child_x(const component &child) const;

		/* Get supposed Y coordinate of the given child. */
		virtual float child_y(const component &child) const;

		/* Get supposed width of the given child. */
		virtual float child_width(const component &child) const;

		/* Get supposed height of the given child. */
		virtual float child_height(const component &child) const;

		/* Will be called when a component is added into this box. */
		virtual void child_added(component &child)
		{}
	};

	template <typename Component, typename ... T>
	box &box::add(T && ... args)
	{
		component &child = children_refs_.emplace_back(*children_.emplace_back(new Component{std::forward<T>(args)...}));

		if (!child.x) child.x = [this, &child] { return child_x(child); };
		if (!child.y) child.y = [this, &child] { return child_y(child); };
		if (!child.width) child.width = [this, &child] { return child_width(child); };
		if (!child.height) child.height = [this, &child] { return child_height(child); };
		if (!child.line_height) child.line_height = [this] { return line_height(); };
		if (!child.font) child.font = [this] { return font(); };
		if (!child.text_color) child.text_color = [this] { return text_color(); };
		if (!child.text_align) child.text_align = [this] { return text_align(); };

		child.parent_ = this;
		child_added(child);

		return *this;
	}
}
