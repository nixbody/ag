#pragma once

#include "border.h"
#include "color.h"
#include "insets.h"

#include <functional>
#include <optional>
#include <utility>

namespace ag
{
	class box;

	/* Base class for UI components. */
	class component
	{
		friend class box;

	public:
		/* Parent reference type. */
		using parent_ref = std::reference_wrapper<box>;

		/* Type of this component's style struct. */
		struct style_type
		{
			/* Style property. */
			template <typename T>
			struct prop : std::function<T ()>
			{
				using std::function<T ()>::function;

				/* Initialize this property with the given value. */
				prop(T &&value): prop{[v = std::forward<T>(value)] { return v; }}
				{}
			};

			/* Visibility flag. */
			prop<bool> visible{true};

			/* Position coordinates. */
			prop<float> x{0.0f}, y{0.0f};

			/* Dimensions. */
			prop<float> width{0.0f}, height{0.0f};

			/* Corners' radius. */
			prop<float> radius{0.0f};
			
			/* Background color. */
			prop<color> bg_color{color{}};

			/* Border. */
			prop<border> border{::ag::border{}};

			/* Padding. */
			prop<insets> padding{0.0f};
		};

		/* Destructor. */
		virtual ~component() = default;
		
		/* Get this component's style. */
		virtual style_type &style() = 0;

		/* Draw this component on the screen. */
		virtual void draw();

		/* Get parent of this component. */
		const std::optional<parent_ref> &parent() const;

		/* Get width of this component. */
		float width();

		/* Get height of this component. */
		float height();

		/* Hide this component. */
		component &hide();

		/* Show this component. */
		component &show();

	private:
		/* Parent of this component. */
		std::optional<parent_ref> parent_;
	};
}
