#pragma once

#include "component.h"
#include "region.h"
#include "type_traits.h"

#include <memory>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

namespace ag
{
	/* Component box. */
	class box : public component
	{
		friend ag::display;

	public:
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

	protected:
		/* Get index of the given child. */
		std::size_t child_index(const component &child) const
		{ return children_indices_.at(&child); }

	private:
		/* Children regions cache. */
		static inline std::unordered_map<const component *, const region> children_regions_cache_;

		/* References to components stored inside this box. */
		std::vector<component_ref> children_refs_;

		/* Components stored inside this box. */
		std::vector<std::unique_ptr<component>> children_;

		/* Children indices lookup table. */
		std::unordered_map<const component *, std::size_t> children_indices_;

		/* Set the display on which this box and its children are drawn. */
		void set_display(ag::display &display) override
		{ display_ = &display; for (component &c : children_refs_) c.set_display(display); }

		/* Draw components stored inside this box. */
		void draw_content() const override
		{ draw_text(text()); for (const component &c : children_refs_) c.draw(); }

		/* Get the region occupied by the given child. */
		const region &child_region(const component &child) const;

		/* Get supposed X coordinate of the given child. */
		virtual float child_x(const component &child) const;

		/* Get supposed Y coordinate of the given child. */
		virtual float child_y(const component &child) const;

		/* Get supposed width of the given child. */
		virtual float child_width(const component &child) const;

		/* Get supposed height of the given child. */
		virtual float child_height(const component &child) const;

		/* Will be called when a component is added into this box. */
		virtual void child_added(component &)
		{}
	};

	template <typename Component, typename ... T>
	box &box::add(T && ... args)
	{
		component &child = children_refs_.emplace_back(*children_.emplace_back(new Component{std::forward<T>(args)...}));
		children_indices_.try_emplace(&child, children_.size() - 1);

		if (!child.theme) child.theme = [this] { return theme(); };
		if (!child.x) child.x = [this, &child] { return child_region(child).x; };
		if (!child.y) child.y = [this, &child] { return child_region(child).y; };
		if (!child.width) child.width = [this, &child] { return child_region(child).width; };
		if (!child.height) child.height = [this, &child] { return child_region(child).height; };
		if (!child.line_height) child.line_height = [this] { return line_height(); };
		if (!child.font) child.font = [this] { return font(); };
		if (!child.text_color) child.text_color = [this] { return text_color(); };
		if (!child.text_align) child.text_align = [this] { return text_align(); };

		child.set_display(*display_);
		child.parent_ = this;
		child_added(child);

		return *this;
	}
}
